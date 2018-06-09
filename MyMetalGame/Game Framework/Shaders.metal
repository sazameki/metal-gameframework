//
//  Shaders.metal
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#include <metal_stdlib>
#include <simd/simd.h>
#import "ShaderTypes.hpp"
#import "AAPLShaderTypes.h"


using namespace metal;


//// Shader 1

struct Vertex
{
    float3 position [[attribute(VertexAttributePosition)]];
    float2 texCoord [[attribute(VertexAttributeTexcoord)]];
};

struct ColorTexInOut
{
    float4 position [[position]];
    float2 texCoord;
};

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

struct ColorInOut
{
    float4 position [[position]];
    float4 color;
};

vertex ColorInOut vertexShader2(uint vertexID [[vertex_id]], constant AAPLVertex *vertices [[buffer(0)]])
{
    ColorInOut out;

    out.position.xy = vertices[vertexID].position.xy;
    out.position.z = 0.0;
    out.position.w = 1.0;
    out.color = vertices[vertexID].color;

    return out;
}

fragment float4 fragmentShader2(ColorInOut in [[stage_in]])
{
    return in.color;
}

