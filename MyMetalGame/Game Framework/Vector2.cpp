//
//  Vector2.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "Vector2.hpp"

#include "Mathf.hpp"
#include "Matrix4x4.hpp"
#include "Quaternion.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "StringSupport.hpp"
#include "GameError.hpp"

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <stdexcept>



#pragma mark - Static 変数

const Vector2& Vector2::down    = Vector2(0.0f, -1.0f);
const Vector2& Vector2::left    = Vector2(-1.0f, 0.0f);
const Vector2& Vector2::one     = Vector2(1.0f, 1.0f);
const Vector2& Vector2::right   = Vector2(1.0f, 0.0f);
const Vector2& Vector2::up      = Vector2(0.0f, 1.0f);
const Vector2& Vector2::zero    = Vector2(0.0f, 0.0f);



# pragma mark - Static 関数

float Vector2::Angle(const Vector2& from, const Vector2& to)
{
    return acosf(Mathf::Clamp(Vector2::Dot(from.Normalized(), to.Normalized()), -1.0f, 1.0f)) * Mathf::Rad2Deg;
}

Vector2 Vector2::ClampMagnitude(const Vector2& vector, float maxLength)
{
    if (vector.SqrMagnitude() > maxLength * maxLength) {
        return vector.Normalized() * maxLength;
    }
    return vector;
}

float Vector2::Cross(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x * rhs.y - lhs.y * rhs.x;
}

float Vector2::Distance(const Vector2& a, const Vector2& b)
{
    return (a - b).Magnitude();
}

float Vector2::Dot(const Vector2& lhs, const Vector2& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::EaseIn(const Vector2& vec1, const Vector2& vec2, float t)
{
    return vec1 + (vec2 - vec1) * (t * t);
}

Vector2 Vector2::EaseInOut(const Vector2& vec1, const Vector2& vec2, float t)
{
    Vector2 middle = (vec1 + vec2) / 2;
    
    t *= 2;
    if (t <= 1.0f) {
        return vec1 + (middle - vec1) * (t * t);
    }
    t -= 1;
    return middle - (vec2 - middle) * (t * (t - 2));
}

Vector2 Vector2::EaseOut(const Vector2& vec1, const Vector2& vec2, float t)
{
    return (vec1 - (vec2 - vec1) * (t * (t - 2)));
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
    t = Mathf::Clamp01(t);
    return a + (b - a) * t;
}

Vector2 Vector2::LerpUnclamped(const Vector2& a, const Vector2& b, float t)
{
    return a + (b - a) * t;
}

Vector2 Vector2::Max(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y));
}

Vector2 Vector2::Min(const Vector2& lhs, const Vector2& rhs)
{
    return Vector2(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y));
}

Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta)
{
    Vector2 a = target - current;
    float magnitude = a.Magnitude();
    if (magnitude <= maxDistanceDelta || magnitude <= FLT_EPSILON) {
        return target;
    }
    return current + a / magnitude * maxDistanceDelta;
}

Vector2 Vector2::Reflect(const Vector2& inDirection, const Vector2& inNormal)
{
    Vector2 theNormal(inNormal);
    theNormal.Normalize();
    return inDirection - 2.0f * Vector2::Dot(inDirection, theNormal) * theNormal;
}

Vector2 Vector2::Scale(const Vector2& a, const Vector2& b)
{
    return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 Vector2::SmoothDamp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
    smoothTime = std::max(0.0001f, smoothTime);
    float num = 2.0f / smoothTime;
    float num2 = num * deltaTime;
    float d = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
    Vector2 vector = current - target;
    Vector2 vector2 = target;
    float maxLength = maxSpeed * smoothTime;
    vector = Vector2::ClampMagnitude(vector, maxLength);
    Vector2 target2 = current - vector;
    Vector2 vector3 = (currentVelocity + num * vector) * deltaTime;
    currentVelocity = (currentVelocity - num * vector3) * d;
    Vector2 vector4 = target2 + (vector + vector3) * d;
    if (Vector2::Dot(vector2 - current, vector4 - vector2) > 0.0f) {
        vector4 = vector2;
        currentVelocity = (vector4 - vector2) / deltaTime;
    }
    return vector4;
}

Vector2 Vector2::SmoothStep(const Vector2& a, const Vector2& b, float t)
{
    float x = Mathf::SmoothStep(a.x, b.x, t);
    float y = Mathf::SmoothStep(a.y, b.y, t);
    return Vector2(x, y);
}


#pragma mark - コンストラクタ

Vector2::Vector2()
    : x(0.0f), y(0.0f)
{
    // Do nothing
}

Vector2::Vector2(float x_, float y_)
    : x(x_), y(y_)
{
    // Do nothing
}

Vector2::Vector2(const Vector2& vec)
    : x(vec.x), y(vec.y)
{
    // Do nothing
}


#pragma mark - Public 関数

float Vector2::Magnitude() const
{
    return sqrtf(x * x + y * y);
}

float Vector2::SqrMagnitude() const
{
    return (x * x + y * y);
}

Vector2 Vector2::Normalized() const
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        return *this / magnitude;
    }
    return Vector2::zero;
}

void Vector2::Normalize()
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        *this /= magnitude;
    } else {
        *this = Vector2::zero;
    }
}

void Vector2::Set(float _x, float _y)
{
    x = _x;
    y = _y;
}

std::string Vector2::ToString() const
{
    return ToString("%.1f");
}

std::string Vector2::ToString(const std::string& format) const
{
    std::string xStr = FormatString(format.c_str(), x);
    std::string yStr = FormatString(format.c_str(), y);
    return FormatString("(%s, %s)", xStr.c_str(), yStr.c_str());
}

const char* Vector2::c_str() const
{
    return GMObject::c_str();
}

const char* Vector2::c_str(const std::string& format) const
{
    return ToString(format).c_str();
}


#pragma mark - 演算子のオーバーロード

Vector2& Vector2::operator=(const Vector2& vec)
{
    x = vec.x;
    y = vec.y;
    return *this;
}

Vector2 Vector2::operator-() const
{
    return Vector2(-x, -y);
}

Vector2 Vector2::operator+(const Vector2& vec) const
{
    return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(const Vector2& vec) const
{
    return Vector2(x - vec.x, y - vec.y);
}

Vector2 Vector2::operator*(const Vector2& vec) const
{
    return Vector2(x * vec.x, y * vec.y);
}

Vector2 Vector2::operator/(const Vector2& vec) const
{
    return Vector2(x / vec.x, y / vec.y);
}

Vector2 Vector2::operator*(float value) const
{
    return Vector2(x * value, y * value);
}

Vector2 Vector2::operator/(float value) const
{
    float d = 1.0f / value;
    return Vector2(x * d, y * d);
}

Vector2 operator*(float value, const Vector2& vec)
{
    return Vector2(vec.x * value, vec.y * value);
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
    x += vec.x;
    y += vec.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
    x -= vec.x;
    y -= vec.y;
    return *this;
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
    x *= vec.x;
    y *= vec.y;
    return *this;    
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
    x /= vec.x;
    y /= vec.y;
    return *this;    
}

Vector2& Vector2::operator*=(float value)
{
    x *= value;
    y *= value;
    return *this;    
}

Vector2& Vector2::operator/=(float value)
{
    x /= value;
    y /= value;
    return *this;    
}

bool Vector2::operator==(const Vector2& vec) const
{
    return ((*this - vec).SqrMagnitude() < 9.99999944E-11f);
}

bool Vector2::operator!=(const Vector2& vec) const
{
    return ((*this - vec).SqrMagnitude() >= 9.99999944E-11f);
}

float& Vector2::operator[](int index)
{
    if (index >= 2) {
        throw GameError("Error: Tried to access Vector2 with an invalid index: %d", index);
    }
    return (index == 0)? x: y;
}

Vector2::operator Vector3() const
{
    return Vector3(x, y, 0.0f);
}

