//
//  Renderer.mm
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#import <simd/simd.h>
#import <ModelIO/ModelIO.h>
#import "GameViewController.hpp"
#import "Renderer.hpp"
#import "ShaderTypes.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "Settings.hpp"
#import "AAPLShaderTypes.h"
#include "BlendMode.hpp"
#include <os/log.h>
#include "DebugSupport.hpp"
#include "StringSupport.hpp"


static id<MTLCommandBuffer> _Nullable   sCommandBuffer;
static MTKView* _Nullable               sMetalView;
static id<MTLBuffer> _Nullable          sMetalVertexBuffer;

static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_Alpha;
static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_Screen;
static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_Add;
static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_Multiply;
static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_Invert;
static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_XOR;
static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_Copy;
static id<MTLRenderPipelineState>  sPipelineState_SimpleDraw_Clear;

static NSUInteger   sPassCount;
static BlendMode    sBlendMode;
static NSUInteger   sBatchedPolygonCount;
static NSUInteger   sVertexBufferOffset;
static AAPLVertex   *sVertexBufferPointer;
static AAPLVertex   *sVertexBufferPointerStart;
static AAPLVertex   *sVertexBufferPointerEdge;
static size_t       sVertexBufferSize;

static const NSUInteger kMaxBuffersInFlight = 3;
static const size_t kAlignedUniformsSize = (sizeof(Uniforms) & ~0xFF) + 0x100;


void Start();
void Update();
void FlushVertexRendering();


void InitRenderingState()
{
    sBlendMode = BlendModeAlpha;
    sBatchedPolygonCount = 0;
    sVertexBufferOffset = 0;
    sVertexBufferPointer = (AAPLVertex *)sMetalVertexBuffer.contents;
    sVertexBufferPointerStart = sVertexBufferPointer;
    sVertexBufferPointerEdge = (AAPLVertex *)((char *)sVertexBufferPointer + sVertexBufferSize);
    sPassCount = 0;
}

void Clear(const Color& color)
{
    // 未処理の頂点バッファが溜まっていれば破棄する
    if (sBatchedPolygonCount > 0) {
        sBatchedPolygonCount = 0;
        sVertexBufferPointer = sVertexBufferPointerStart;
    }

    MTLRenderPassDescriptor *renderPassDescriptor = sMetalView.currentRenderPassDescriptor;

    if (renderPassDescriptor) {
        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(color.r, color.g, color.b, color.a);
        renderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear;
        renderPassDescriptor.depthAttachment.clearDepth = 1.0f;
        renderPassDescriptor.stencilAttachment.loadAction = MTLLoadActionClear;
        renderPassDescriptor.stencilAttachment.clearStencil = 0;

        id <MTLRenderCommandEncoder> renderEncoder = [sCommandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        [renderEncoder endEncoding];

        sPassCount++;
    }
}

void SetBlendMode(BlendMode blendMode)
{
    // 頂点バッファが溜まっていれば吐き出す
    if (sBatchedPolygonCount > 0) {
        FlushVertexRendering();
    }
    sBlendMode = blendMode;
}

void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& c1, const Color& c2, const Color& c3)
{
    // ポリゴンの数が設定された最大個数を超えていないことをチェックする
    if (sVertexBufferPointer + 3 > sVertexBufferPointerEdge) {
        AbortGame("頂点バッファのメモリ領域を超えてポリゴン情報を格納しようとしました。（最大ポリゴン数は約 %u）", METAL_MAX_POLYGON_COUNT);
    }

    // 頂点バッファにデータを書き込む
    sVertexBufferPointer->position.x = p1.x;
    sVertexBufferPointer->position.y = p1.y;
    sVertexBufferPointer->color.r = c1.r;
    sVertexBufferPointer->color.g = c1.g;
    sVertexBufferPointer->color.b = c1.b;
    sVertexBufferPointer->color.a = c1.a;
    sVertexBufferPointer++;

    sVertexBufferPointer->position.x = p2.x;
    sVertexBufferPointer->position.y = p2.y;
    sVertexBufferPointer->color.r = c2.r;
    sVertexBufferPointer->color.g = c2.g;
    sVertexBufferPointer->color.b = c2.b;
    sVertexBufferPointer->color.a = c2.a;
    sVertexBufferPointer++;

    sVertexBufferPointer->position.x = p3.x;
    sVertexBufferPointer->position.y = p3.y;
    sVertexBufferPointer->color.r = c3.r;
    sVertexBufferPointer->color.g = c3.g;
    sVertexBufferPointer->color.b = c3.b;
    sVertexBufferPointer->color.a = c3.a;
    sVertexBufferPointer++;

    sBatchedPolygonCount++;
}


id<MTLRenderPipelineState> GetPipelineStateForSimpleDrawing()
{
    if (sBlendMode == BlendModeNone) {
        return sPipelineState_SimpleDraw_Alpha;
    } else if (sBlendMode == BlendModeScreen) {
        return sPipelineState_SimpleDraw_Screen;
    } else if (sBlendMode == BlendModeAdd) {
        return sPipelineState_SimpleDraw_Add;
    } else if (sBlendMode == BlendModeMultiply) {
        return sPipelineState_SimpleDraw_Multiply;
    } else if (sBlendMode == BlendModeInvert) {
        return sPipelineState_SimpleDraw_Invert;
    } else if (sBlendMode == BlendModeXOR) {
        return sPipelineState_SimpleDraw_XOR;
    } else if (sBlendMode == BlendModeCopy) {
        return sPipelineState_SimpleDraw_Copy;
    } else if (sBlendMode == BlendModeClear) {
        return sPipelineState_SimpleDraw_Clear;
    } else {
        return sPipelineState_SimpleDraw_Alpha;
    }
}

void FlushVertexRendering()
{
    MTLRenderPassDescriptor *renderPassDescriptor = sMetalView.currentRenderPassDescriptor;

    if (renderPassDescriptor) {
        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionDontCare;
        renderPassDescriptor.depthAttachment.loadAction = MTLLoadActionDontCare;
        renderPassDescriptor.stencilAttachment.loadAction = MTLLoadActionDontCare;

        id<MTLRenderCommandEncoder> renderEncoder = [sCommandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        renderEncoder.label = @"MyRenderEncoder";

        [renderEncoder setRenderPipelineState:GetPipelineStateForSimpleDrawing()];
        [renderEncoder setVertexBuffer:sMetalVertexBuffer offset:sVertexBufferOffset atIndex:0];
        [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:sBatchedPolygonCount*3];
        [renderEncoder endEncoding];

        sVertexBufferOffset += sizeof(AAPLVertex) * sBatchedPolygonCount * 3;
        sVertexBufferOffset = ((sVertexBufferOffset - 1) & ~0xff) + 0x100;
        sVertexBufferPointer = (AAPLVertex *)((char *)sMetalVertexBuffer.contents + sVertexBufferOffset);
        sVertexBufferPointerStart = sVertexBufferPointer;

        sBatchedPolygonCount = 0;
    }
}


@implementation Renderer
{
    dispatch_semaphore_t    _inFlightSemaphore;
    id <MTLDevice>          _device;
    id <MTLCommandQueue>    _commandQueue;

    id<MTLBuffer>               _dynamicUniformBuffer;
    id<MTLRenderPipelineState>  _pipelineState;

    id<MTLDepthStencilState>    _depthState;
    id<MTLTexture>              _colorMap;
    MTLVertexDescriptor         *_mtlVertexDescriptor;

    uint32_t    _uniformBufferOffset;
    uint8_t     _uniformBufferIndex;
    void        *_uniformBufferAddress;

    Matrix4x4   projMat;

    MTKMesh     *_mesh;
    float       _rotation;

    vector_uint2 _viewportSize;

    id<MTLBuffer>   metalVertexBuffer;
}

-(nonnull instancetype)initWithMetalKitView:(nonnull MTKView *)view;
{
    self = [super init];
    if (self) {
        _device = view.device;
        _inFlightSemaphore = dispatch_semaphore_create(kMaxBuffersInFlight);
        [self _loadMetalWithView:view];
        [self _loadAssets];
    }

    return self;
}

- (id<MTLRenderPipelineState>)createTextureDrawingPipelineWithLibrary:(id<MTLLibrary>)metalLib view:(nonnull MTKView *)view
{
    _mtlVertexDescriptor = [[MTLVertexDescriptor alloc] init];

    _mtlVertexDescriptor.attributes[VertexAttributePosition].format = MTLVertexFormatFloat3;
    _mtlVertexDescriptor.attributes[VertexAttributePosition].offset = 0;
    _mtlVertexDescriptor.attributes[VertexAttributePosition].bufferIndex = BufferIndexMeshPositions;

    _mtlVertexDescriptor.attributes[VertexAttributeTexcoord].format = MTLVertexFormatFloat2;
    _mtlVertexDescriptor.attributes[VertexAttributeTexcoord].offset = 0;
    _mtlVertexDescriptor.attributes[VertexAttributeTexcoord].bufferIndex = BufferIndexMeshGenerics;

    _mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stride = 12;
    _mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stepRate = 1;
    _mtlVertexDescriptor.layouts[BufferIndexMeshPositions].stepFunction = MTLVertexStepFunctionPerVertex;

    _mtlVertexDescriptor.layouts[BufferIndexMeshGenerics].stride = 8;
    _mtlVertexDescriptor.layouts[BufferIndexMeshGenerics].stepRate = 1;
    _mtlVertexDescriptor.layouts[BufferIndexMeshGenerics].stepFunction = MTLVertexStepFunctionPerVertex;

    id<MTLFunction> vfunc = [metalLib newFunctionWithName:@"vertexShader"];
    id<MTLFunction> ffunc = [metalLib newFunctionWithName:@"fragmentShader"];

    MTLRenderPipelineDescriptor *desc = [[MTLRenderPipelineDescriptor alloc] init];
    desc.label = @"MyPipeline";
    desc.sampleCount = view.sampleCount;
    desc.vertexFunction = vfunc;
    desc.fragmentFunction = ffunc;
    desc.vertexDescriptor = _mtlVertexDescriptor;
    desc.colorAttachments[0].pixelFormat = view.colorPixelFormat;
    desc.depthAttachmentPixelFormat = view.depthStencilPixelFormat;
    desc.stencilAttachmentPixelFormat = view.depthStencilPixelFormat;

    NSError *error = NULL;
    id<MTLRenderPipelineState> ret = [_device newRenderPipelineStateWithDescriptor:desc error:&error];
    if (!ret) {
        NSLog(@"Failed to created pipeline state, error %@", error);
    }
    return ret;
}

- (id<MTLRenderPipelineState>)createSimpleDrawingPipelineWithLibrary:(id<MTLLibrary>)metalLib view:(nonnull MTKView *)view blendMode:(BlendMode)blendMode
{
    id<MTLFunction> vfunc = [metalLib newFunctionWithName:@"vertexShader2"];
    id<MTLFunction> ffunc = [metalLib newFunctionWithName:@"fragmentShader2"];

    MTLRenderPipelineDescriptor *desc = [[MTLRenderPipelineDescriptor alloc] init];
    desc.label = @"MyPipeline2";
    desc.vertexFunction = vfunc;
    desc.fragmentFunction = ffunc;
    desc.colorAttachments[0].pixelFormat = view.colorPixelFormat;
    desc.depthAttachmentPixelFormat = view.depthStencilPixelFormat;
    desc.stencilAttachmentPixelFormat = view.depthStencilPixelFormat;

    if (blendMode == BlendModeNone) {
    } else if (blendMode == BlendModeCopy) {
        // コピー合成
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOne;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOne;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    } else if (blendMode == BlendModeClear) {
        // クリア合成
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    } else if (blendMode == BlendModeXOR) {
        // XOR合成
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOneMinusDestinationColor;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceColor;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOneMinusDestinationAlpha;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    } else if (blendMode == BlendModeInvert) {
        // 反転合成
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOneMinusDestinationColor;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOneMinusDestinationAlpha;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    } else if (blendMode == BlendModeMultiply) {
        // 乗算合成
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorSourceColor;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorZero;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorSourceAlpha;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    } else if (blendMode == BlendModeAdd) {
        // 加算合成（覆い焼き（リニア））
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOne;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOne;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    } else if (blendMode == BlendModeScreen) {
        os_log(OS_LOG_DEFAULT, "screen-blend");
        // スクリーン合成
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorOneMinusDestinationColor;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOne;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorOneMinusDestinationAlpha;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOne;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    } else {
        // アルファ合成
        desc.colorAttachments[0].blendingEnabled = YES;
        desc.colorAttachments[0].sourceRGBBlendFactor = MTLBlendFactorSourceAlpha;
        desc.colorAttachments[0].destinationRGBBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
        desc.colorAttachments[0].rgbBlendOperation = MTLBlendOperationAdd;
        desc.colorAttachments[0].sourceAlphaBlendFactor = MTLBlendFactorSourceAlpha;
        desc.colorAttachments[0].destinationAlphaBlendFactor = MTLBlendFactorOneMinusSourceAlpha;
        desc.colorAttachments[0].alphaBlendOperation = MTLBlendOperationAdd;
    }

    NSError *error = NULL;
    id<MTLRenderPipelineState> ret = [_device newRenderPipelineStateWithDescriptor:desc error:&error];
    if (!ret) {
        NSLog(@"Failed to created pipeline state for simple drawing: Error=\"%@\"", error);
    }
    return ret;
}

- (void)_loadMetalWithView:(nonnull MTKView *)view
{
    sMetalView = view;

    view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    view.colorPixelFormat = MTLPixelFormatBGRA8Unorm;
    //view.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    view.sampleCount = 1;

    // 頂点データのバッファを用意する
    sVertexBufferSize = sizeof(AAPLVertex) * METAL_MAX_POLYGON_COUNT * 3;
    sMetalVertexBuffer = [_device newBufferWithLength:sVertexBufferSize options:MTLResourceStorageModeShared];
    sMetalVertexBuffer.label = @"MetalVertexBuffer";

    // シェーダを使ったパイプラインの用意
    id<MTLLibrary> metalLib = [_device newDefaultLibrary];
    _pipelineState = [self createTextureDrawingPipelineWithLibrary:metalLib view:view];
    sPipelineState_SimpleDraw_Alpha = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeAlpha];
    sPipelineState_SimpleDraw_Screen = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeScreen];
    sPipelineState_SimpleDraw_Add = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeAdd];
    sPipelineState_SimpleDraw_Multiply = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeMultiply];
    sPipelineState_SimpleDraw_Invert = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeInvert];
    sPipelineState_SimpleDraw_XOR = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeXOR];
    sPipelineState_SimpleDraw_Copy = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeCopy];
    sPipelineState_SimpleDraw_Clear = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeClear];

    MTLDepthStencilDescriptor *depthStateDesc = [[MTLDepthStencilDescriptor alloc] init];
    depthStateDesc.depthCompareFunction = MTLCompareFunctionLess;
    depthStateDesc.depthWriteEnabled = YES;
    _depthState = [_device newDepthStencilStateWithDescriptor:depthStateDesc];

    NSUInteger uniformBufferSize = kAlignedUniformsSize * kMaxBuffersInFlight;

    _dynamicUniformBuffer = [_device newBufferWithLength:uniformBufferSize
                                                 options:MTLResourceStorageModeShared];

    _dynamicUniformBuffer.label = @"UniformBuffer";

    _commandQueue = [_device newCommandQueue];
}

- (void)_loadAssets
{
    /// Load assets into metal objects
    MTKMeshBufferAllocator *metalAllocator = [[MTKMeshBufferAllocator alloc] initWithDevice:_device];

    MDLMesh *mdlMesh = [MDLMesh newBoxWithDimensions:(vector_float3){4, 4, 4}
                                            segments:(vector_uint3){2, 2, 2}
                                        geometryType:MDLGeometryTypeTriangles
                                       inwardNormals:NO
                                           allocator:metalAllocator];

    MDLVertexDescriptor *mdlVertexDescriptor = MTKModelIOVertexDescriptorFromMetal(_mtlVertexDescriptor);
    mdlVertexDescriptor.attributes[VertexAttributePosition].name = MDLVertexAttributePosition;
    mdlVertexDescriptor.attributes[VertexAttributeTexcoord].name = MDLVertexAttributeTextureCoordinate;

    mdlMesh.vertexDescriptor = mdlVertexDescriptor;

    NSError *error;
    _mesh = [[MTKMesh alloc] initWithMesh:mdlMesh
                                   device:_device
                                    error:&error];

    if (!_mesh || error) {
        NSLog(@"Error creating MetalKit mesh %@", error.localizedDescription);
    }

    MTKTextureLoader *textureLoader = [[MTKTextureLoader alloc] initWithDevice:_device];

    NSDictionary *textureLoaderOptions = @{
        MTKTextureLoaderOptionTextureUsage      : @(MTLTextureUsageShaderRead),
        MTKTextureLoaderOptionTextureStorageMode: @(MTLStorageModePrivate)
    };

    _colorMap = [textureLoader newTextureWithName:@"ColorMap"
                                      scaleFactor:1.0
                                           bundle:nil
                                          options:textureLoaderOptions
                                            error:&error];

    if (!_colorMap || error) {
        NSLog(@"Error creating texture %@", error.localizedDescription);
    }

    Start();
}

- (void)_updateDynamicBufferState
{
    _uniformBufferIndex = (_uniformBufferIndex + 1) % kMaxBuffersInFlight;
    _uniformBufferOffset = kAlignedUniformsSize * _uniformBufferIndex;
    _uniformBufferAddress = ((uint8_t *)_dynamicUniformBuffer.contents) + _uniformBufferOffset;
}

- (void)_updateGameState
{
    Uniforms *uniforms = (Uniforms *)_uniformBufferAddress;
    uniforms->projectionMatrix = *(matrix_float4x4 *)projMat.mat;

    {
        Matrix4x4 mat = Matrix4x4::identity;
        mat *= Matrix4x4::Rotate(Quaternion::AngleAxis(_rotation * Mathf::Rad2Deg, Vector3(1, 1, 0)));
        mat *= Matrix4x4::Translation(-3, -1, -8);
        uniforms->modelViewMatrix = *(matrix_float4x4 *)mat.mat;
    }

    _rotation += .01;
}

- (void)drawBoxWithView:(nonnull MTKView *)view commandBuffer:(id<MTLCommandBuffer>)commandBuffer
{
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;

    if (renderPassDescriptor) {
        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionDontCare;
        renderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear;
        renderPassDescriptor.depthAttachment.clearDepth = 1.0f;

        /// Final pass rendering code here
        id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        renderEncoder.label = @"MyRenderEncoder";

        [renderEncoder setFrontFacingWinding:MTLWindingCounterClockwise];
        [renderEncoder setCullMode:MTLCullModeBack];
        [renderEncoder setRenderPipelineState:_pipelineState];
        [renderEncoder setDepthStencilState:_depthState];

        [renderEncoder setVertexBuffer:_dynamicUniformBuffer
                                offset:_uniformBufferOffset
                               atIndex:BufferIndexUniforms];
        [renderEncoder setFragmentBuffer:_dynamicUniformBuffer
                                  offset:_uniformBufferOffset
                                 atIndex:BufferIndexUniforms];

        for (NSUInteger bufferIndex = 0; bufferIndex < _mesh.vertexBuffers.count; bufferIndex++) {
            MTKMeshBuffer *vertexBuffer = _mesh.vertexBuffers[bufferIndex];
            if ((NSNull *)vertexBuffer != [NSNull null]) {
                [renderEncoder setVertexBuffer:vertexBuffer.buffer
                                        offset:vertexBuffer.offset
                                       atIndex:bufferIndex];
            }
        }

        [renderEncoder setFragmentTexture:_colorMap
                                  atIndex:TextureIndexColor];

        for (MTKSubmesh *submesh in _mesh.submeshes) {
            [renderEncoder drawIndexedPrimitives:submesh.primitiveType
                                      indexCount:submesh.indexCount
                                       indexType:submesh.indexType
                                     indexBuffer:submesh.indexBuffer.buffer
                               indexBufferOffset:submesh.indexBuffer.offset];
        }

        [renderEncoder endEncoding];
    }
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    //os_log(OS_LOG_DEFAULT, "/------\\");
    dispatch_semaphore_wait(_inFlightSemaphore, DISPATCH_TIME_FOREVER);

    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    commandBuffer.label = @"MyCommand";
    sCommandBuffer = commandBuffer;

    __block dispatch_semaphore_t block_sema = _inFlightSemaphore;
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        dispatch_semaphore_signal(block_sema);
    }];

    [self _updateDynamicBufferState];
    [self _updateGameState];

    Input::__UpdateTriggers();
    Time::__Update();

    InitRenderingState();
    Update();

    // バッチ処理のデータがあれば吐き出す
    if (sBatchedPolygonCount > 0) {
        FlushVertexRendering();
    }

    //[self drawBoxWithView:view commandBuffer:commandBuffer];
    //passCount++;

    if (sPassCount > 0) {
        [commandBuffer presentDrawable:view.currentDrawable];
        [commandBuffer commit];
    }

    Time::frameCount++;

    //os_log(OS_LOG_DEFAULT, "\\------/");
}

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size
{
    float aspect = size.width / (float)size.height;
    projMat = Matrix4x4::Perspective(65.0f * Mathf::Deg2Rad, aspect, 0.1f, 100.0f);
    //_projectionMatrix = matrix_perspective_right_hand(65.0f * (M_PI / 180.0f), aspect, 0.1f, 100.0f);

    _viewportSize.x = size.width;
    _viewportSize.y = size.height;
}

@end
