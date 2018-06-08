/*
See LICENSE folder for this sample’s licensing information.

Abstract:
Header containing types and enum constants shared between Metal shaders and C/ObjC source
*/

#ifndef AAPLShaderTypes_h
#define AAPLShaderTypes_h

#include <simd/simd.h>

typedef struct
{
    vector_float2 position;
    vector_float4 color;
} AAPLVertex;

typedef struct
{
    vector_float3 position;
    vector_float4 color;
    vector_float3 normal;
    vector_float2 uv;
} AAPLVertexFull;

#endif /* AAPLShaderTypes_h */
