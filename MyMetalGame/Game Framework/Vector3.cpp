//
//  Vector3.cpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Mathf.hpp"
#include "GameError.hpp"
#include "StringSupport.hpp"

#include <algorithm>
#include <cfloat>
#include <cmath>


#pragma mark - Static 変数

const Vector3& Vector3::back        = Vector3(0.0f, 0.0f, -1.0f);
const Vector3& Vector3::down        = Vector3(0.0f, -1.0f, 0.0f);
const Vector3& Vector3::forward     = Vector3(0.0f, 0.0f, 1.0f);
const Vector3& Vector3::left        = Vector3(-1.0f, 0.0f, 0.0f);
const Vector3& Vector3::one         = Vector3(1.0f, 1.0f, 1.0f);
const Vector3& Vector3::right       = Vector3(1.0f, 0.0f, 0.0f);
const Vector3& Vector3::up          = Vector3(0.0f, 1.0f, 0.0f);
const Vector3& Vector3::zero        = Vector3(0.0f, 0.0f, 0.0f);



#pragma mark - Static 関数

float Vector3::Angle(const Vector3& from, const Vector3& to)
{
    return acosf(Mathf::Clamp(Vector3::Dot(from.Normalized(), to.Normalized()), -1.0f, 1.0f)) * Mathf::Rad2Deg;
}

Vector3 Vector3::ClampMagnitude(const Vector3& vector, float maxLength)
{
    if (vector.SqrMagnitude() > maxLength * maxLength) {
        return vector.Normalized() * maxLength;
    }
    return vector;
}

Vector3 Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs)
{
    return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
                   lhs.z * rhs.x - lhs.x * rhs.z,
                   lhs.x * rhs.y - lhs.y * rhs.x);
}

float Vector3::Distance(const Vector3& a, const Vector3& b)
{
    return (a - b).Magnitude();
}

float Vector3::Dot(const Vector3& lhs, const Vector3& rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::EaseIn(const Vector3& vec1, const Vector3& vec2, float t)
{
    return vec1 + (vec2 - vec1) * (t * t);
}

Vector3 Vector3::EaseInOut(const Vector3& vec1, const Vector3& vec2, float t)
{
    Vector3 middle = (vec1 + vec2) / 2;
    
    t *= 2;
    if (t <= 1.0f) {
        return vec1 + (middle - vec1) * (t * t);
    }
    t -= 1;
    return middle - (vec2 - middle) * (t * (t - 2));
}

Vector3 Vector3::EaseOut(const Vector3& vec1, const Vector3& vec2, float t)
{
    return (vec1 - (vec2 - vec1) * (t * (t - 2)));
}

Vector3 Vector3::Lerp(const Vector3& vec1, const Vector3& vec2, float t)
{
    t = Mathf::Clamp01(t);
    return vec1 + (vec2 - vec1) * t;
}

Vector3 Vector3::LerpUnclamped(const Vector3& vec1, const Vector3& vec2, float t)
{
    return vec1 + (vec2 - vec1) * t;
}

Vector3 Vector3::Max(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z));
}

Vector3 Vector3::Min(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z));
}

Vector3 Vector3::MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta)
{
    Vector3 a = target - current;
    float magnitude = a.Magnitude();
    if (magnitude <= maxDistanceDelta || magnitude == 0.0f) {
        return target;
    }
    return current + a / magnitude * maxDistanceDelta;
}

Vector3 Vector3::Project(const Vector3& vector, const Vector3& onNormal)
{
    float num = Vector3::Dot(onNormal, onNormal);
    if (num < FLT_EPSILON) {
        return Vector3::zero;
    }
    return onNormal * Vector3::Dot(vector, onNormal) / num;
}

Vector3 Vector3::ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal)
{
    return vector - Vector3::Project(vector, planeNormal);
}

Vector3 Vector3::Reflect(const Vector3 &inDirection, const Vector3 &inNormal)
{
    return -2.0f * Vector3::Dot(inNormal, inDirection) * inNormal + inDirection;
}

Vector3 Vector3::Scale(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 Vector3::Slerp(const Vector3& a, const Vector3& b, float t)
{
    t = Mathf::Clamp01(t);

    float dot = Vector3::Dot(a.Normalized(), b.Normalized());
    Vector3 b2 = b;
    if (dot < 0.0f) {
        b2 *= -1;
        dot = -dot;
    }

    if (dot < 0.95f) {
        float angle = acosf(dot);
        return Vector3(a * sinf(angle * (1.0f - t)) + b2 * sinf(angle * t)) / sinf(angle);
    } else {
        return Lerp(a, b, t);
    }
}

Vector3 Vector3::SlerpUnclamped(const Vector3& a, const Vector3& b, float t)
{
    float dot = Vector3::Dot(a.Normalized(), b.Normalized());
    Vector3 b2 = b;
    if (dot < 0.0f) {
        b2 *= -1;
        dot = -dot;
    }

    if (dot < 0.95f) {
        float angle = acosf(dot);
        return Vector3(a * sinf(angle * (1.0f - t)) + b2 * sinf(angle * t)) / sinf(angle);
    } else {
        return LerpUnclamped(a, b, t);
    }
}

Vector3 Vector3::SmoothDamp(const Vector3 &current, const Vector3 &target, Vector3 &currentVelocity,
                            float smoothTime, float maxSpeed, float deltaTime)
{
    smoothTime = std::max(0.0001f, smoothTime);
    float num = 2.0f / smoothTime;
    float num2 = num * deltaTime;
    float d = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
    Vector3 vector = current - target;
    Vector3 vector2 = target;
    float maxLength = maxSpeed * smoothTime;
    vector = Vector3::ClampMagnitude(vector, maxLength);
    Vector3 target2 = current - vector;
    Vector3 vector3 = (currentVelocity + num * vector) * deltaTime;
    currentVelocity = (currentVelocity - num * vector3) * d;
    Vector3 vector4 = target2 + (vector + vector3) * d;
    if (Vector3::Dot(vector2 - current, vector4 - vector2) > 0.0f) {
        vector4 = vector2;
        currentVelocity = (vector4 - vector2) / deltaTime;
    }
    return vector4;
}

Vector3 Vector3::SmoothStep(const Vector3& a, const Vector3& b, float t)
{
    float x = Mathf::SmoothStep(a.x, b.x, t);
    float y = Mathf::SmoothStep(a.y, b.y, t);
    float z = Mathf::SmoothStep(a.z, b.z, t);
    return Vector3(x, y, z);
}


#pragma mark - コンストラクタ

Vector3::Vector3()
    : x(0.0f), y(0.0f), z(0.0f)
{
    // Do nothing
}

Vector3::Vector3(float x_, float y_, float z_)
    : x(x_), y(y_), z(z_)
{
    // Do nothing
}

Vector3::Vector3(const Vector2& vec, float z_)
    : x(vec.x), y(vec.y), z(z_)
{
    // Do nothing
}

Vector3::Vector3(const Vector3& vec)
    : x(vec.x), y(vec.y), z(vec.z)
{
    // Do nothing
}


#pragma mark - Public 関数

float Vector3::Magnitude() const
{
    return sqrtf(x * x + y * y + z * z);
}

float Vector3::SqrMagnitude() const
{
    return (x * x + y * y + z * z);
}

Vector3 Vector3::Normalized() const
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        return *this / magnitude;
    }
    return Vector3::zero;
}

void Vector3::Normalize()
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        *this /= magnitude;
    } else {
        *this = Vector3::zero;
    }
}

void Vector3::Set(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}

std::string Vector3::ToString() const
{
    return ToString("%.1f");
}

std::string Vector3::ToString(const std::string& format) const
{
    std::string xStr = FormatString(format.c_str(), x);
    std::string yStr = FormatString(format.c_str(), y);
    std::string zStr = FormatString(format.c_str(), z);
    return FormatString("(%s, %s, %s)", xStr.c_str(), yStr.c_str(), zStr.c_str());
}

const char* Vector3::c_str() const
{
    return GMObject::c_str();
}

const char* Vector3::c_str(const std::string& format) const
{
    return ToString(format).c_str();
}


#pragma mark - 演算子のオーバーロード

Vector3& Vector3::operator=(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+(const Vector3& vec) const
{
    return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3& vec) const
{
    return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

Vector3 Vector3::operator*(const Vector3& vec) const
{
    return Vector3(x * vec.x, y * vec.y, z * vec.z);
}

Vector3 Vector3::operator/(const Vector3& vec) const
{
    return Vector3(x / vec.x, y / vec.y, z / vec.z);
}

Vector3 Vector3::operator*(float value) const
{
    return Vector3(x * value, y * value, z * value);
}

Vector3 Vector3::operator/(float value) const
{
    return Vector3(x / value, y / value, z / value);
}

Vector3 operator*(float value, const Vector3& vec)
{
    return Vector3(vec.x * value, vec.y * value, vec.z * value);
}

Vector3& Vector3::operator+=(const Vector3& vec)
{
    x += vec.x;
    y += vec.y;
    z += vec.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& vec)
{
    x -= vec.x;
    y -= vec.y;
    z -= vec.z;
    return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec)
{
    x *= vec.x;
    y *= vec.y;
    z *= vec.z;
    return *this;
}

Vector3& Vector3::operator/=(const Vector3& vec)
{
    x /= vec.x;
    y /= vec.y;
    z /= vec.z;
    return *this;
}

Vector3& Vector3::operator*=(float value)
{
    x *= value;
    y *= value;
    z *= value;
    return *this;
}

Vector3& Vector3::operator/=(float value)
{
    x /= value;
    y /= value;
    z /= value;
    return *this;
}

bool Vector3::operator==(const Vector3& vec) const
{
    return ((*this - vec).SqrMagnitude() < 9.99999944E-11f);
}

bool Vector3::operator!=(const Vector3& vec) const
{
    return ((*this - vec).SqrMagnitude() >= 9.99999944E-11f);
}

float& Vector3::operator[](int index)
{
    if (index >= 3) {
        throw GameError("Error: Tried to access Vector3 with an invalid index: %d", index);
    }
    return (index == 0)? x: (index == 1)? y: z;
}

Vector3::operator Vector2() const
{
    return Vector2(x, y);
}


