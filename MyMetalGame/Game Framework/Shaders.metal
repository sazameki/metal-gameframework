//
//  Shaders.metal
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

// File for Metal kernel and shader functions

#include <metal_stdlib>
#include <simd/simd.h>

// Including header shared between this Metal shader code and Swift/C code executing Metal API commands
#import "ShaderTypes.hpp"

#import "AAPLShaderTypes.h"

using namespace metal;


//// Shader 1

typedef struct
{
    float3 position [[attribute(VertexAttributePosition)]];
    float2 texCoord [[attribute(VertexAttributeTexcoord)]];
} Vertex;

typedef struct
{
    float4 position [[position]];
    float2 texCoord;
} ColorTexInOut;

vertex ColorTexInOut vertexShader(Vertex in [[stage_in]],
                               constant Uniforms &uniforms[[buffer(BufferIndexUniforms)]])
{
    ColorTexInOut out;

    float4 position = float4(in.position, 1.0);
    out.position = uniforms.projectionMatrix * uniforms.modelViewMatrix * position;
    out.texCoord = in.texCoord;

    return out;
}

fragment float4 fragmentShader(ColorTexInOut in [[stage_in]],
                               constant Uniforms & uniforms [[ buffer(BufferIndexUniforms) ]],
                               texture2d<half> colorMap     [[ texture(TextureIndexColor) ]])
{
    constexpr sampler colorSampler(mip_filter::linear,
                                   mag_filter::linear,
                                   min_filter::linear);

    half4 colorSample = colorMap.sample(colorSampler, in.texCoord.xy);
    return float4(colorSample);
}


//// Shader 2
/*
typedef struct
{
    vector_float2 position;
    vector_float4 color;
} ColorVertex;

typedef struct
{
    float4 position [[position]];
    float4 color;
} ColorInOut;

vertex ColorInOut vertexShader2(uint vertexID[[vertex_id]], constant ColorVertex *vertices[[buffer(0)]])
{
    ColorInOut out;
    out.position = float4(vertices[vertexID].position.xy, 1.0, 1.0);
    out.color = vertices[vertexID].color;
    return out;
}

fragment float4 fragmentShader2(ColorVertex in[[stage_in]])
{
    return in.color;
}
*/

typedef struct
{
    float4 clipSpacePosition [[position]];
    float4 color;

} RasterizerData;

vertex RasterizerData vertexShader2(uint vertexID [[vertex_id]], constant AAPLVertex *vertices [[buffer(0)]])
{
    RasterizerData out;

    out.clipSpacePosition.xy = vertices[vertexID].position.xy;
    out.clipSpacePosition.z = 0.0;
    out.clipSpacePosition.w = 1.0;
    out.color = vertices[vertexID].color;

    return out;
}

fragment float4 fragmentShader2(RasterizerData in [[stage_in]])
{
    // We return the color we just set which will be written to our color attachment.
    return in.color;
}

