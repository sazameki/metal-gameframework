#ifndef AAPLShaderTypes_h
#define AAPLShaderTypes_h

#include <simd/simd.h>

using namespace simd;

struct AAPLVertex
{
    float2          position;
    packed_float4   color;
};

struct AAPLVertexFull
{
    simd::float3    position;
    simd::float4    color;
    simd::float3    normal;
    simd::float2    uv;
};

#endif /* AAPLShaderTypes_h */
