//
//  Vector4.cpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "Vector4.hpp"

#include "Mathf.hpp"
#include "Matrix4x4.hpp"
#include "Quaternion.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "GameError.hpp"
#include "StringSupport.hpp"

#include <cfloat>
#include <cmath>


#pragma mark - Static 変数

const Vector4& Vector4::one   = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
const Vector4& Vector4::zero  = Vector4(0.0f, 0.0f, 0.0f, 0.0f);


#pragma mark - Static 関数

float Vector4::Distance(const Vector2& a, const Vector2& b)
{
    return (a - b).Magnitude();
}

float Vector4::Dot(const Vector4& a, const Vector4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vector4 Vector4::EaseIn(const Vector4& vec1, const Vector4& vec2, float t)
{
    return vec1 + (vec2 - vec1) * (t * t);
}

Vector4 Vector4::EaseInOut(const Vector4& vec1, const Vector4& vec2, float t)
{
    Vector4 middle = (vec1 + vec2) / 2;
    
    t *= 2;
    if (t <= 1.0f) {
        return vec1 + (middle - vec1) * (t * t);
    }
    t -= 1;
    return middle - (vec2 - middle) * (t * (t - 2));
}

Vector4 Vector4::EaseOut(const Vector4& vec1, const Vector4& vec2, float t)
{
    return (vec1 - (vec2 - vec1) * (t * (t - 2)));
}

Vector4 Vector4::Lerp(const Vector4& vec1, const Vector4& vec2, float t)
{
    t = Mathf::Clamp01(t);
    return vec1 + (vec2 - vec1) * t;
}

Vector4 Vector4::LerpUnclamped(const Vector4& vec1, const Vector4& vec2, float t)
{
    return vec1 + (vec2 - vec1) * t;
}

Vector4 Vector4::Max(const Vector4& vec1, const Vector4& vec2)
{
    Vector4 ret = vec1;
    if (vec2.x > ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y > ret.y) {
        ret.y = vec2.y;
    }
    if (vec2.z > ret.z) {
        ret.z = vec2.z;
    }
    if (vec2.w > ret.w) {
        ret.w = vec2.w;
    }
    return ret;
}

Vector4 Vector4::Min(const Vector4& vec1, const Vector4& vec2)
{
    Vector4 ret = vec1;
    if (vec2.x < ret.x) {
        ret.x = vec2.x;
    }
    if (vec2.y < ret.y) {
        ret.y = vec2.y;
    }
    if (vec2.z < ret.z) {
        ret.z = vec2.z;
    }
    if (vec2.w < ret.w) {
        ret.w = vec2.w;
    }
    return ret;    
}

Vector4 Vector4::MoveTowards(const Vector4& current, const Vector4& target, float maxDistanceDelta)
{
    Vector4 a = target - current;
    float magnitude = a.Magnitude();
    if (magnitude <= maxDistanceDelta || magnitude == 0.0f) {
        return target;
    }
    return current + a / magnitude * maxDistanceDelta;
}

Vector4 Vector4::Project(const Vector4& vector, const Vector4& onNormal)
{
    float num = Vector4::Dot(onNormal, onNormal);
    if (num < FLT_EPSILON) {
        return Vector4::zero;
    }
    return onNormal * Vector4::Dot(vector, onNormal) / num;
}

Vector4 Vector4::Scale(const Vector4& a, const Vector4& b)
{
    return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

Vector4 Vector4::SmoothStep(const Vector4& a, const Vector4& b, float t)
{
    float x = Mathf::SmoothStep(a.x, b.x, t);
    float y = Mathf::SmoothStep(a.y, b.y, t);
    float z = Mathf::SmoothStep(a.z, b.z, t);
    float w = Mathf::SmoothStep(a.w, b.w, t);
    return Vector4(x, y, z, w);
}


#pragma mark - コンストラクタ

Vector4::Vector4()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
    // Do nothing
}

Vector4::Vector4(float x_, float y_, float z_, float w_)
    : x(x_), y(y_), z(z_), w(w_)
{
    // Do nothing
}

Vector4::Vector4(const Vector2& vec, float z_, float w_)
    : x(vec.x), y(vec.y), z(z_), w(w_)
{
    // Do nothing
}

Vector4::Vector4(const Vector3& vec, float w_)
    : x(vec.x), y(vec.y), z(vec.z), w(w_)
{
    // Do nothing
}

Vector4::Vector4(const Vector4& vec)
    : x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{
    // Do nothing
}


#pragma mark - Public 関数

float Vector4::Magnitude() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::SqrMagnitude() const
{
    return (x * x + y * y + z * z + w * w);
}

Vector4 Vector4::Normalized() const
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        return *this / magnitude;
    }
    return Vector4::zero;
}

void Vector4::Normalize()
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        *this /= magnitude;
    } else {
        *this = Vector4::zero;
    }
}

void Vector4::Set(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

std::string Vector4::ToString() const
{
    return ToString("%.1f");
}

std::string Vector4::ToString(const std::string& format) const
{
    std::string xStr = FormatString(format.c_str(), x);
    std::string yStr = FormatString(format.c_str(), y);
    std::string zStr = FormatString(format.c_str(), z);
    std::string wStr = FormatString(format.c_str(), w);
    return FormatString("(%s, %s, %s, %s)", xStr.c_str(), yStr.c_str(), zStr.c_str(), wStr.c_str());
}

const char* Vector4::c_str() const
{
    return GMObject::c_str();
}

const char* Vector4::c_str(const std::string& format) const
{
    return ToString(format).c_str();
}


#pragma mark - 演算子のオーバーロード

Vector4& Vector4::operator=(const Vector4& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    w = vec.w;
    return *this;
}

Vector4 Vector4::operator-() const
{
    return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+(const Vector4& vec) const
{
    return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

Vector4 Vector4::operator-(const Vector4& vec) const
{
    return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vector4 Vector4::operator*(const Vector4& vec) const
{
    return Vector4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

Vector4 Vector4::operator/(const Vector4& vec) const
{
    return Vector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
}

Vector4 Vector4::operator*(float value) const
{
    return Vector4(x * value, y * value, z * value, w * value);
}

Vector4 Vector4::operator/(float value) const
{
    float d = 1.0f / value;
    return Vector4(x * d, y * d, z * d, w * d);
}

Vector4 operator*(float value, const Vector4& vec)
{
    return Vector4(vec.x * value, vec.y * value, vec.z * value, vec.w * value);
}

Vector4& Vector4::operator+=(const Vector4& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    w += vec.w;
    return *this;
}

Vector4& Vector4::operator-=(const Vector4& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    w -= vec.w;
    return *this;
}

Vector4& Vector4::operator*=(const Vector4& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    w *= vec.w;
    return *this;
}

Vector4& Vector4::operator/=(const Vector4& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    w /= vec.w;
    return *this;
}

Vector4& Vector4::operator*=(float value)
{
    x *= value;
    y *= value;
    z *= value;
    w *= value;
    return *this;
}

Vector4& Vector4::operator/=(float value)
{
    float d = 1.0f / value;
    x *= d;
    y *= d;
    z *= d;
    w *= d;
    return *this;
}

bool Vector4::operator==(const Vector4& vec) const
{
    return ((*this - vec).SqrMagnitude() < 9.99999944E-11f);
}

bool Vector4::operator!=(const Vector4& vec) const
{
    return ((*this - vec).SqrMagnitude() >= 9.99999944E-11f);
}

float& Vector4::operator[](int index)
{
    if (index >= 4) {
        throw GameError("Error: Tried to access Vector4 with an invalid index: %d", index);
    }
    return (index == 0)? x: (index == 1)? y: (index == 2)? z: w;
}


