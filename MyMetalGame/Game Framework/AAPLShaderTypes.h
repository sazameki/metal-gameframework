#ifndef AAPLShaderTypes_h
#define AAPLShaderTypes_h

#include <simd/simd.h>

struct AAPLVertex
{
    simd::float2    position;
    simd::float4    color;
};

struct AAPLVertexFull
{
    simd::float3    position;
    simd::float4    color;
    simd::float3    normal;
    simd::float2    uv;
};

#endif /* AAPLShaderTypes_h */
