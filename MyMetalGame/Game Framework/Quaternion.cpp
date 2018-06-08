//
//  Quaternion.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "Quaternion.hpp"

#include "Types.hpp"
#include "Mathf.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "StringSupport.hpp"

#include <algorithm>
#include <cmath>


#pragma mark - Static 変数

const Quaternion& Quaternion::identity  = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);


#pragma mark - Static 関数

float Quaternion::Angle(const Quaternion& a, const Quaternion& b)
{
    float f = Quaternion::Dot(a, b);
    return acosf(std::min(fabsf(f), 1.0f)) * 2.0f * Mathf::Rad2Deg;
}

Quaternion Quaternion::AngleAxis(float degree, const Vector3& axis)
{
    if (axis.SqrMagnitude() <= __FLT_EPSILON__) {
        return identity;
    }

    float rad = degree * Mathf::Deg2Rad;
    rad *= 0.5f;
    Vector3 axis_n = axis.Normalized();
    axis_n = axis_n * sinf(rad);

    Quaternion ret;

    ret.x = axis_n.x;
    ret.y = axis_n.y;
    ret.z = axis_n.z;
    ret.w = cosf(rad);

    return ret;
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Quaternion Quaternion::Euler(float x, float y, float z)
{
    x *= Mathf::Deg2Rad;
    y *= Mathf::Deg2Rad;
    z *= Mathf::Deg2Rad;

    float cx = cosf(x / 2);
    float cy = cosf(y / 2);
    float cz = cosf(z / 2);
    float sx = sinf(x / 2);
    float sy = sinf(y / 2);
    float sz = sinf(z / 2);

    return Quaternion(sx*cy*cz + cx*sy*sz,
                      cx*sy*cz - sx*cy*sz,
                      cx*cy*sz - sx*sy*cz,
                      cx*cy*cz + sx*sy*sz);
}

Quaternion Quaternion::Euler(const Vector3& euler)
{
    float x = euler.x * Mathf::Deg2Rad;
    float y = euler.y * Mathf::Deg2Rad;
    float z = euler.z * Mathf::Deg2Rad;

    float cx = cosf(x / 2);
    float cy = cosf(y / 2);
    float cz = cosf(z / 2);
    float sx = sinf(x / 2);
    float sy = sinf(y / 2);
    float sz = sinf(z / 2);

    return Quaternion(sx*cy*cz + cx*sy*sz,
                      cx*sy*cz - sx*cy*sz,
                      cx*cy*sz - sx*sy*cz,
                      cx*cy*cz + sx*sy*sz);
}

Quaternion Quaternion::EaseIn(const Quaternion& q1, const Quaternion& q2, float t)
{
    return q1 + (q2 - q1) * (t * t);
}

Quaternion Quaternion::EaseInOut(const Quaternion& q1, const Quaternion& q2, float t)
{
    Quaternion middle = (q1 + q2) / 2;
    
    t *= 2;
    if (t <= 1.0f) {
        return q1 + (middle - q1) * (t * t);
    }
    t -= 1;
    return middle - (q2 - middle) * (t * (t - 2));
}

Quaternion Quaternion::EaseOut(const Quaternion& q1, const Quaternion& q2, float t)
{
    return (q1 - (q2 - q1) * (t * (t - 2)));
}

Quaternion Quaternion::FromToRotation(const Vector3& fromDir, const Vector3& toDir)
{
    // cf. http://www.xnainfo.com/content.php?content=18

    Vector3 src = fromDir.Normalized();
    Vector3 dest = toDir.Normalized();

    float d = Vector3::Dot(src, dest);

    if (d >= 1.0f) {
        return Quaternion::identity;
    } else if (d < (1e-6f - 1.0f)) {
        Vector3 axis = Vector3::Cross(Vector3::right, src);
        if (axis.SqrMagnitude() == 0.0f) {
            axis = Vector3::Cross(Vector3::up, src);
        }
        axis.Normalize();
        return Quaternion::AngleAxis(180.0f, axis);
    } else {
        float s = sqrtf((1.0f + d) * 2.0f);
        Vector3 c = Vector3::Cross(src, dest);
        c *= 1.0f / s;
        return Quaternion(c.x, c.y, c.z, 0.5f * s).Normalized();
    }
}

Quaternion Quaternion::Inverse(const Quaternion& rotation)
{
    Quaternion ret(rotation);
    ret.Conjugate();
    ret /= rotation.SqrMagnitude();
    return ret;
}

Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    t = Mathf::Clamp01(t);
    return q1 * (1.0f - t) + q2 * t;
}

Quaternion Quaternion::LerpUnclamped(const Quaternion& q1, const Quaternion& q2, float t)
{
    return q1 * (1.0f - t) + q2 * t;
}

Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& upwards)
{
    return Matrix4x4::LookAt(Vector3::zero, -forward, upwards).Transpose().ToQuaternion();
}

Quaternion Quaternion::RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta)
{
    float num = Quaternion::Angle(from, to);
    if (num == 0.0f) {
        return to;
    }
    float t = std::min(1.0f, maxDegreesDelta / num);
    return Quaternion::SlerpUnclamped(from, to, t);
}

Quaternion Quaternion::Slerp(const Quaternion& q1, const Quaternion& q2, float t)
{
    t = Mathf::Clamp01(t);

    float dot = Quaternion::Dot(q1, q2);
    Quaternion q3 = q2;
    if (dot < 0.0f) {
        q3 *= -1;
        dot = -dot;
    }
    
    if (dot < 0.95f) {
        float angle = acosf(dot);
        return (q1 * sinf(angle * (1.0f - t)) + q3 * sinf(angle * t)) / sinf(angle);
    } else {
        return Lerp(q1, q3, t);
    }
}

Quaternion Quaternion::SlerpUnclamped(const Quaternion& q1, const Quaternion& q2, float t)
{
    float dot = Quaternion::Dot(q1, q2);

    Quaternion q3 = q2;
    if (dot < 0.0f) {
        q3 *= -1;
        dot = -dot;
    }

    if (dot < 0.95f) {
        float angle = acosf(dot);
        return (q1 * sinf(angle * (1.0f - t)) + q3 * sinf(angle * t)) / sinf(angle);
    } else {
        return Lerp(q1, q3, t);
    }
}

Quaternion Quaternion::SmoothStep(const Quaternion& a, const Quaternion& b, float t)
{
    return Vector4::SmoothStep(a, b, t);
}


#pragma mark - コンストラクタ

Quaternion::Quaternion()
    : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{
    // Do nothing
}

Quaternion::Quaternion(float x_, float y_, float z_, float w_)
    : x(x_), y(y_), z(z_), w(w_)
{
    // Do nothing
}

Quaternion::Quaternion(const Quaternion& quat)
    : x(quat.x), y(quat.y), z(quat.z), w(quat.w)
{
    // Do nothing
}

Quaternion::Quaternion(const Vector4& vec)
    : x(vec.x),y(vec.y), z(vec.z), w(vec.w)
{
    // Do nothing
}

Quaternion::Quaternion(const Matrix4x4& m)
{
    float m00 = m.m00;
    float m11 = m.m11;
    float m22 = m.m22;
    
    float tr = m00 + m11 + m22;
    
    if (tr > 0.0f) {
        float t = sqrtf(tr + 1.0f) * 2;
        x = (m.m12 - m.m21) / t;
        y = (m.m20 - m.m02) / t; 
        z = (m.m01 - m.m10) / t;
        w = t / 4;
    } else if (m00 >= m11 && m00 >= m22) {
        float t = sqrtf(m00 - m11 - m22 + 1.0f) * 2;
        x = t / 4;
        y = (m.m10 + m.m01) / t;
        z = (m.m20 + m.m02) / t;
        w = (m.m12 - m.m21) / t;
    } else if (m11 > m22) {
        float t = sqrtf(m11 - m00 - m22 + 1.0f) * 2;
        x = (m.m10 + m.m01) / t;
        y = t / 4;
        z = (m.m21 + m.m12) / t;
        w = (m.m20 - m.m02) / t;
    } else {
        float t = sqrtf(m22 - m00 - m11 + 1.0f) * 2;
        x = (m.m20 + m.m02) / t;
        y = (m.m21 + m.m12) / t;
        z = t / 4;
        w = (m.m01 - m.m10) / t;
    }
}


#pragma mark - Public 関数

Quaternion Quaternion::Concat(const Quaternion& quat) const
{
    return quat * (*this);
}

Quaternion& Quaternion::Conjugate()
{
    x *= -1;
    y *= -1;
    z *= -1;
    return *this;
}

float Quaternion::Magnitude() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

Quaternion Quaternion::Normalized() const
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        return *this / magnitude;
    }
    return Quaternion();
}

void Quaternion::Normalize()
{
    float magnitude = Magnitude();
    if (magnitude > 1E-05f) {
        *this /= magnitude;
    } else {
        this->Set(0.0f, 0.0f, 0.0f, 0.0f);
    }
}

void Quaternion::Set(float new_x, float new_y, float new_z, float new_w)
{
    x = new_x;
    y = new_y;
    z = new_z;
    w = new_w;
}

float Quaternion::SqrMagnitude() const
{
    return x * x + y * y + z * z + w * w;
}

Matrix4x4 Quaternion::ToMatrix4x4() const
{
    return Matrix4x4(*this);
}

std::string Quaternion::ToString() const
{
    return ToString("%.1f");
}

std::string Quaternion::ToString(const std::string& format) const
{
    std::string xStr = FormatString(format.c_str(), x);
    std::string yStr = FormatString(format.c_str(), y);
    std::string zStr = FormatString(format.c_str(), z);
    std::string wStr = FormatString(format.c_str(), w);
    return FormatString("(%s, %s, %s, %s)", xStr.c_str(), yStr.c_str(), zStr.c_str(), wStr.c_str());
}

const char* Quaternion::c_str() const
{
    return GMObject::c_str();
}

const char* Quaternion::c_str(const std::string& format) const
{
    return ToString(format).c_str();
}


#pragma mark - 演算子のオーバーロード

Quaternion& Quaternion::operator=(const Quaternion& quat)
{
    x = quat.x;
    y = quat.y;
    z = quat.z;
    w = quat.w;
    return *this;
}

Quaternion Quaternion::operator-() const
{
    Quaternion ret(*this);
    ret *= -1;
    return ret;
}

Quaternion Quaternion::operator+(const Quaternion& quat) const
{
    Quaternion ret(*this);
    ret += quat;
    return ret;
}

Quaternion Quaternion::operator-(const Quaternion& quat) const
{
    Quaternion ret(*this);
    ret -= quat;
    return ret;
}

Quaternion Quaternion::operator*(const Quaternion& quat) const
{
    Quaternion ret(*this);
    ret *= quat;
    return ret;
}

Quaternion Quaternion::operator*(float scale) const
{
    Quaternion ret(*this);
    ret.x *= scale;
    ret.y *= scale;
    ret.z *= scale;
    ret.w *= scale;
    return ret;
}

Vector2 Quaternion::operator*(const Vector2& vec) const
{
    Vector4 v4 = *this * Vector4(vec, 1.0f);
    return Vector2(v4.x, v4.y);
}

Vector3 Quaternion::operator*(const Vector3& vec) const
{
    Vector4 v4 = *this * Vector4(vec, 1.0f);
    return Vector3(v4.x, v4.y, v4.z);
}

Vector4 Quaternion::operator*(const Vector4& vec) const
{
    Quaternion conj(*this);
    conj.Conjugate();

    Quaternion p(vec.x, vec.y, vec.z, vec.w);
    p = *this * p;
    p = p * conj;

    return Vector4(p.x, p.y, p.z, p.w);
}

Quaternion Quaternion::operator/(const Quaternion& quat) const
{
    Quaternion ret(*this);
    ret /= quat;
    return ret;
}

Quaternion Quaternion::operator/(float value) const
{
    Quaternion ret(*this);
    ret.x /= value;
    ret.y /= value;
    ret.z /= value;
    ret.w /= value;
    return ret;
}

Quaternion& Quaternion::operator+=(const Quaternion& quat)
{
    x += quat.x;
    y += quat.y;
    z += quat.z;
    w += quat.w;
    return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& quat)
{
    x -= quat.x;
    y -= quat.y;
    z -= quat.z;
    w -= quat.w;
    return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& quat)
{
    float tx = x;
    float ty = y;
    float tz = z;
    float tw = w;

    x = tw * quat.x + tx * quat.w + ty * quat.z - tz * quat.y;
    y = tw * quat.y - tx * quat.z + ty * quat.w + tz * quat.x;
    z = tw * quat.z + tx * quat.y - ty * quat.x + tz * quat.w;
    w = tw * quat.w - tx * quat.x - ty * quat.y - tz * quat.z;

    return *this;
}

Quaternion& Quaternion::operator*=(float scale)
{
    x *= scale;
    y *= scale;
    z *= scale;
    w *= scale;
    return *this;
}

Quaternion& Quaternion::operator/=(const Quaternion& quat)
{
    float tx = x;
    float ty = y;
    float tz = z;
    float tw = w;

    float magnitude = Magnitude();

    x = (-tw * quat.x + tx * quat.w - ty * quat.z + tz * quat.y) / magnitude;
    y = (-tw * quat.y + tx * quat.z + ty * quat.w - tz * quat.x) / magnitude;
    z = (-tw * quat.z - tx * quat.y + ty * quat.x + tz * quat.w) / magnitude;
    w = ( tw * quat.w + tx * quat.x + ty * quat.y + tz * quat.z) / magnitude;

    return *this;
}

Quaternion& Quaternion::operator/=(float value)
{
    x /= value;
    y /= value;
    z /= value;
    w /= value;
    return *this;
}

bool Quaternion::operator==(const Quaternion& quat) const
{
    return Quaternion::Dot(*this, quat) > 0.999f;
}

bool Quaternion::operator!=(const Quaternion& quat) const
{
    return Quaternion::Dot(*this, quat) <= 0.999f;
}

Quaternion::operator Vector4() const
{
    return Vector4(x, y, z, w);
}


