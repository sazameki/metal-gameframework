//
//  Renderer.mm
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright © 2018 Satoshi Numata. All rights reserved.
//

#import <simd/simd.h>
#import <ModelIO/ModelIO.h>
#import "GameViewController.hpp"
#import "Renderer.hpp"
#import "ShaderTypes.hpp"
#include "Input.hpp"
#include "Time.hpp"
#include "DrawCommand.hpp"
#include "Settings.hpp"
#import "AAPLShaderTypes.h"
#import <os/log.h>


static const NSUInteger kMaxBuffersInFlight = 3;
static const size_t kAlignedUniformsSize = (sizeof(Uniforms) & ~0xFF) + 0x100;


void Start();
void Update();


@implementation Renderer
{
    dispatch_semaphore_t    _inFlightSemaphore;
    id <MTLDevice>          _device;
    id <MTLCommandQueue>    _commandQueue;

    id<MTLBuffer>               _dynamicUniformBuffer;
    id<MTLRenderPipelineState>  _pipelineState;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_Alpha;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_Screen;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_Add;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_Multiply;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_Invert;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_XOR;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_Copy;
    id<MTLRenderPipelineState>  pipelineState_SimpleDraw_Clear;

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

    BlendMode blendMode;

    id<MTLBuffer>   metalVertexBuffer;
    unsigned batchedPolygonCount;
    AAPLVertex *pBatchBuffer;
    AAPLVertex *pBatchStart;
    size_t bufferOffset;
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
    view.depthStencilPixelFormat = MTLPixelFormatDepth32Float_Stencil8;
    view.colorPixelFormat = MTLPixelFormatBGRA8Unorm;
    //view.colorPixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
    view.sampleCount = 1;

    // 頂点データのバッファを用意する
    size_t batchBufferFrameSize = sizeof(AAPLVertex) * METAL_POLYGON_BATCH_SIZE * 3;
    metalVertexBuffer = [_device newBufferWithLength:batchBufferFrameSize options:MTLResourceStorageModeShared];
    metalVertexBuffer.label = @"MetalVertexBuffer";

    // シェーダを使ったパイプラインの用意
    id<MTLLibrary> metalLib = [_device newDefaultLibrary];
    _pipelineState = [self createTextureDrawingPipelineWithLibrary:metalLib view:view];
    pipelineState_SimpleDraw_Alpha = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeAlpha];
    pipelineState_SimpleDraw_Screen = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeScreen];
    pipelineState_SimpleDraw_Add = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeAdd];
    pipelineState_SimpleDraw_Multiply = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeMultiply];
    pipelineState_SimpleDraw_Invert = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeInvert];
    pipelineState_SimpleDraw_XOR = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeXOR];
    pipelineState_SimpleDraw_Copy = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeCopy];
    pipelineState_SimpleDraw_Clear = [self createSimpleDrawingPipelineWithLibrary:metalLib view:view blendMode:BlendModeClear];

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

- (void)performClearPassWithCommand:(DrawCommand *)command view:(nonnull MTKView *)view commandBuffer:(id<MTLCommandBuffer>)commandBuffer
{
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;

    if (renderPassDescriptor) {
        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionClear;
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColorMake(command->colors[0].r, command->colors[0].g, command->colors[0].b, 1.0);
        renderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear;
        renderPassDescriptor.depthAttachment.clearDepth = 1.0f;
        renderPassDescriptor.stencilAttachment.loadAction = MTLLoadActionClear;
        renderPassDescriptor.stencilAttachment.clearStencil = 0;

        id <MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        [renderEncoder endEncoding];
    }
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

- (id<MTLRenderPipelineState>)pipelineStateForSimpleDrawing
{
    if (blendMode == BlendModeNone) {
        return pipelineState_SimpleDraw_Alpha;
    } else if (blendMode == BlendModeScreen) {
        return pipelineState_SimpleDraw_Screen;
    } else if (blendMode == BlendModeAdd) {
        return pipelineState_SimpleDraw_Add;
    } else if (blendMode == BlendModeMultiply) {
        return pipelineState_SimpleDraw_Multiply;
    } else if (blendMode == BlendModeInvert) {
        return pipelineState_SimpleDraw_Invert;
    } else if (blendMode == BlendModeXOR) {
        return pipelineState_SimpleDraw_XOR;
    } else if (blendMode == BlendModeCopy) {
        return pipelineState_SimpleDraw_Copy;
    } else if (blendMode == BlendModeClear) {
        return pipelineState_SimpleDraw_Clear;
    } else {
        return pipelineState_SimpleDraw_Alpha;
    }
}

- (void)flushBatchedDataWithView:(nonnull MTKView *)view commandBuffer:(id<MTLCommandBuffer>)commandBuffer
{
    //os_log(OS_LOG_DEFAULT, "FLUSH %u polygons", batchedPolygonCount);
    MTLRenderPassDescriptor *renderPassDescriptor = view.currentRenderPassDescriptor;

    if (renderPassDescriptor) {
        renderPassDescriptor.colorAttachments[0].loadAction = MTLLoadActionDontCare;
        renderPassDescriptor.depthAttachment.loadAction = MTLLoadActionDontCare;

        id<MTLRenderCommandEncoder> renderEncoder = [commandBuffer renderCommandEncoderWithDescriptor:renderPassDescriptor];
        renderEncoder.label = @"MyRenderEncoder";

        [renderEncoder setRenderPipelineState:[self pipelineStateForSimpleDrawing]];
        //[renderEncoder setVertexBytes:vertexBuffer length:sizeof(AAPLVertex)*batchedPolygonCount*3 atIndex:0];
        //[renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:batchedPolygonCount*3];
        [renderEncoder setVertexBuffer:metalVertexBuffer offset:bufferOffset atIndex:0];
        [renderEncoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:batchedPolygonCount*3];
        [renderEncoder endEncoding];

        bufferOffset += sizeof(AAPLVertex) * batchedPolygonCount * 3;
        bufferOffset = ((bufferOffset - 1) & ~0xff) + 0x100;

        batchedPolygonCount = 0;
    }
}

- (void)drawInMTKView:(nonnull MTKView *)view
{
    //os_log(OS_LOG_DEFAULT, "/------\\");
    /// Per frame updates here
    dispatch_semaphore_wait(_inFlightSemaphore, DISPATCH_TIME_FOREVER);

    id<MTLCommandBuffer> commandBuffer = [_commandQueue commandBuffer];
    commandBuffer.label = @"MyCommand";

    __block dispatch_semaphore_t block_sema = _inFlightSemaphore;
    [commandBuffer addCompletedHandler:^(id<MTLCommandBuffer> buffer) {
        dispatch_semaphore_signal(block_sema);
    }];

    [self _updateDynamicBufferState];
    [self _updateGameState];

    Input::__UpdateTriggers();
    Time::__Update();
    Update();
    Time::frameCount++;

    // 描画コマンドの処理
    unsigned passCount = 0;
    blendMode = BlendModeAlpha;
    batchedPolygonCount = 0;
    pBatchBuffer = (AAPLVertex *)metalVertexBuffer.contents;
    bufferOffset = 0;
    for (DrawCommand &command : gDrawCommands) {
        // Clearコマンド
        if (command.type == DrawCommandType_Clear) {
            // バッチ処理のデータがある場合、いずれ消えるのでデータを破棄する
            if (batchedPolygonCount > 0) {
                batchedPolygonCount = 0;
            }
            // クリア用のパスの実行
            [self performClearPassWithCommand:&command view:view commandBuffer:commandBuffer];
            passCount++;
        }
        // ブレンドモードの設定
        else if (command.type == DrawCommandType_SetBlendMode) {
            // バッチ処理のデータがある場合、吐き出してしまう
            if (batchedPolygonCount > 0) {
                [self flushBatchedDataWithView:view commandBuffer:commandBuffer];
                passCount++;
            }
            // ブレンドモードを変更
            blendMode = command.blendMode;
        }
        // ポリゴンの塗りつぶし
        else if (command.type == DrawCommandType_FillTriangle) {
            // TODO: 異なる種類（単純描画とテクスチャ描画）の描画が来た場合に、直前までのデータを吐き出す処理を追加する。
            // バッチ処理のデータを追加する
            for (int i = 0; i < 3; i++) {
                pBatchBuffer->position.x = command.pos[i].x;
                pBatchBuffer->position.y = command.pos[i].y;
                pBatchBuffer->color.r = command.colors[i].r;
                pBatchBuffer->color.g = command.colors[i].g;
                pBatchBuffer->color.b = command.colors[i].b;
                pBatchBuffer->color.a = command.colors[i].a;
                pBatchBuffer++;
            }
            batchedPolygonCount++;

            // バッチ処理可能な最大ポリゴン数を超えていれば吐き出す
            if (batchedPolygonCount >= METAL_POLYGON_BATCH_SIZE) {
                [self flushBatchedDataWithView:view commandBuffer:commandBuffer];
                passCount++;
            }
        }
    }
    // バッチ処理のデータがあれば吐き出す
    if (batchedPolygonCount > 0) {
        [self flushBatchedDataWithView:view commandBuffer:commandBuffer];
        passCount++;
    }
    gDrawCommands.clear();

    //[self drawBoxWithView:view commandBuffer:commandBuffer];
    //passCount++;

    if (passCount > 0) {
        [commandBuffer presentDrawable:view.currentDrawable];
        [commandBuffer commit];
    }

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
