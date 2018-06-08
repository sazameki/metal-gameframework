//
//  Mathf.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#include "Mathf.hpp"

#include <algorithm>
#include <cfloat>
#include <climits>
#include <cmath>
#include <cstdlib>
//#include "Debug.hpp"


const float Mathf::Deg2Rad = M_PI * 2.0f / 360.0f;
const float Mathf::Epsilon  = FLT_EPSILON;
const float Mathf::Infinity = INFINITY;
const float Mathf::NegativeInfinity = -INFINITY;
const float Mathf::PI = M_PI;
const float Mathf::Rad2Deg = 360.0f / (M_PI * 2.0f);


float Mathf::Abs(float f)
{
    return fabsf(f);
}

float Mathf::Acos(float f)
{
    return acosf(f);
}

bool Mathf::Approximately(float a, float b)
{
    return (fabsf(a - b) < 9.99999944E-11f);
}

float Mathf::Asin(float f)
{
    return asinf(f);
}

float Mathf::Atan(float f)
{
    return atanf(f);
}

float Mathf::Atan2(float y, float x)
{
    return atan2f(y, x);
}

float Mathf::Ceil(float f)
{
    return ceilf(f);
}

int Mathf::CeilToInt(float f)
{
    return (int)ceilf(f);
}

float Mathf::Clamp(float value, float min, float max)
{
    return std::min(std::max(value, min), max);
}

float Mathf::Clamp01(float value)
{
    return Clamp(value, 0.0f, 1.0f);
}

int Mathf::ClosestPowerOfTwo(int value)
{
    if (value <= 0) {
        return 0;
    }
    
    int prev = 0;
    int ret = 1;
    while (ret < INT_MAX/2) {
        if (ret >= value) {
            if (abs(ret - value) > abs(value - prev)) {
                ret = prev;
            }
            break;
        }
        prev = ret;
        ret *= 2;
    }
    return ret;
}

float Mathf::Cos(float f)
{
    return cosf(f);
}

float Mathf::DeltaAngle(float current, float target)
{
    float ret = Mathf::Repeat(target - current, 360.0f);
    if (ret > 180.0f) {
        ret -= 360.0f;
    }
    return ret;
}

float Mathf::EaseIn(float value1, float value2, float t)
{
    return value1 + (value2 - value1) * (t * t);
}

float Mathf::EaseInOut(float value1, float value2, float t)
{
    float middle = (value1 + value2) / 2;
    
    t *= 2;
    if (t <= 1.0f) {
        return value1 + (middle - value1) * (t * t);
    }
    t -= 1;
    return middle - (value2 - middle) * (t * (t - 2));
}

float Mathf::EaseOut(float value1, float value2, float t)
{
    return value1 - (value2 - value1) * (t * (t - 2));
}

float Mathf::Exp(float x)
{
    return expf(x);
}

float Mathf::Floor(float f)
{
    return floorf(f);
}

int Mathf::FloorToInt(float f)
{
    return (int)floorf(f);
}

bool Mathf::IsPowerOfTwo(int value)
{
    if (value < 0) {
        return false;
    }
    if (value == 0) {
        return true;
    }
    return ((value & (value-1)) == 0);
}

float Mathf::InverseLerp(float from, float to, float value)
{
    if (from < to) {
        if (value < from) {
            return 0.0f;
        }
        if (value > to) {
            return 1.0f;
        }
        value -= from;
        value /= to - from;
        return value;
    } else {
        if (from <= to) {
            return 0.0f;
        }
        if (value < to) {
            return 1.0f;
        }
        if (value > from) {
            return 0.0f;
        }
        return 1.0f - (value - to) / (from - to);
    }
}

float Mathf::Lerp(float a, float b, float t)
{
    return a + (b - a) * Clamp01(t);
}

float Mathf::LerpAngle(float a, float b, float t)
{
    float num = Mathf::Repeat(b - a, 360.0f);
    if (num > 180.0f) {
        num -= 360.0f;
    }
    return a + num * Mathf::Clamp01(t);
}

float Mathf::LerpUnclamped(float a, float b, float t)
{
    return a + (b - a) * t;
}

float Mathf::Log(float x)
{
    return logf(x);
}

float Mathf::Log(float f, float p)
{
    return logf(f) / logf(p);
}

float Mathf::Log10(float x)
{
    return log10f(x);
}

float Mathf::Max(float a, float b)
{
    return (a >= b)? a: b;
}

float Mathf::Min(float a, float b)
{
    return (a <= b)? a: b;
}

float Mathf::MoveTowards(float current, float target, float maxDelta)
{
    if (fabsf(target - current) <= maxDelta) {
        return target;
    }
    return current + Mathf::Sign(target - current) * maxDelta;
}

float Mathf::MoveTowardsAngle(float current, float target, float maxDelta)
{
    target = current + Mathf::DeltaAngle(current, target);
    return Mathf::MoveTowards(current, target, maxDelta);
}

int Mathf::NextPowerOfTwo(int value)
{
    if (value <= 0) {
        return 0;
    }
    
    int ret = 1;
    while (ret < INT_MAX/2) {
        if (ret >= value) {
            break;
        }
        ret *= 2;
    }
    return ret;
}

float Mathf::PingPong(float t, float length)
{
    t = Mathf::Repeat(t, length * 2.0f);
    return length - fabsf(t - length);
}

float Mathf::Pow(float f, float p)
{
    return powf(f, p);
}

float Mathf::Repeat(float t, float length)
{
    return t - floorf(t / length) * length;
}

float Mathf::Round(float f)
{
    return roundf(f);
}

int Mathf::RoundToInt(float f)
{
    return (int)roundf(f);
}

float Mathf::Sign(float f)
{
    return (f < 0.0f)? -1.0f: 1.0f;
}

float Mathf::Sin(float rad)
{
    return sinf(rad);
}

float Mathf::SmoothDamp(float current, float target, float& outCurrentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
    smoothTime = std::max(0.0001f, smoothTime);
    float num = 2.0f / smoothTime;
    float num2 = num * deltaTime;
    float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
    float num4 = current - target;
    float num5 = target;
    float num6 = maxSpeed * smoothTime;
    num4 = Mathf::Clamp(num4, -num6, num6);
    target = current - num4;
    float num7 = (outCurrentVelocity + num * num4) * deltaTime;
    outCurrentVelocity = (outCurrentVelocity - num * num7) * num3;
    float num8 = target + (num4 + num7) * num3;
    if (((num5 - current > 0.0f)? 1: 0) == ((num8 > num5)? 1: 0)) {
        num8 = num5;
        outCurrentVelocity = (num8 - num5) / deltaTime;
    }
    return num8;
}

float Mathf::SmoothDampAngle(float current, float target, float& outCurrentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
    target = current + Mathf::DeltaAngle(current, target);
    return Mathf::SmoothDamp(current, target, outCurrentVelocity, smoothTime, maxSpeed, deltaTime);
}

float Mathf::SmoothStep(float from, float to, float t)
{
    t = Mathf::Clamp01(t);
    t = -2.0f * t * t * t + 3.0f * t * t;
    return to * t + from * (1.0f - t);
}

float Mathf::Sqrt(float f)
{
    return sqrtf(f);
}

float Mathf::Tan(float rad)
{
    return tanf(rad);
}


