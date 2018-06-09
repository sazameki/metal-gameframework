//
//  Matrix4x4.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
//

#include "Matrix4x4.hpp"

#include "Types.hpp"
#include "Mathf.hpp"
#include "Quaternion.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "DebugSupport.hpp"
#include "StringSupport.hpp"

#include <cmath>


#pragma mark - Static 変数

const Matrix4x4& Matrix4x4::identity = Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
                                                 0.0f, 1.0f, 0.0f, 0.0f,
                                                 0.0f, 0.0f, 1.0f, 0.0f,
                                                 0.0f, 0.0f, 0.0f, 1.0f);

const Matrix4x4& Matrix4x4::zero = Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 0.0f,
                                             0.0f, 0.0f, 0.0f, 0.0f);


#pragma mark - Static 関数

Matrix4x4 Matrix4x4::Billboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& cameraUpVec)
{
    Vector3 translation = objectPos - cameraPos;
    Vector3 backwards = translation.Normalized();
    Vector3 up = cameraUpVec.Normalized();
    Vector3 right = Vector3::Cross(backwards, up);
    up = Vector3::Cross(backwards, right);

    Matrix4x4 ret(Matrix4x4::identity);
    ret.SetBackward(backwards);
    ret.SetRight(right);
    ret.SetUp(up);
    ret.SetTranslation(translation);
    
    return ret;
}

Matrix4x4 Matrix4x4::ConstrainedBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& rotateAxis,
                                              const Vector3& cameraForwardVec, const Vector3& objectForwardVec)
{
    Matrix4x4 ret;

    // TODO: Matrix4x4::CreateConstrainedBillboard() の実装
    
    return ret;
}

// cf. http://msdn.microsoft.com/en-us/library/bb205343(v=VS.85).aspx
Matrix4x4 Matrix4x4::LookAt(const Vector3& from, const Vector3& to, const Vector3& up)
{
    Vector3 f = (from - to).Normalized();
    Vector3 s = Vector3::Cross(up, f).Normalized();
    Vector3 u = Vector3::Cross(f, s);
    
    return Matrix4x4(s.x, u.x, f.x, 0.0f,
                     s.y, u.y, f.y, 0.0f,
                     s.z, u.z, f.z, 0.0f,
                     -Vector3::Dot(s, from), -Vector3::Dot(u, from), -Vector3::Dot(f, from), 1.0f);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205348(v=VS.85).aspx
Matrix4x4 Matrix4x4::Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    return Matrix4x4(2.0f / (right - left), 0.0f              , 0.0f              , 0.0f,
                    0.0f               , 2.0f / (top - bottom), 0.0f               , 0.0f,
                    0.0f               , 0.0f               , 1.0f / (zNear - zFar), 0.0f,
                    (left + right) / (left - right), (top + bottom) / (bottom - top) , zNear / (zNear - zFar) , 1.0f);
}

// cf. http://msdn.microsoft.com/en-us/library/bb205351(v=vs.85).aspx
// cf. http://msdn.microsoft.com/en-us/library/bb147302(v=vs.85).aspx
Matrix4x4 Matrix4x4::Perspective(float fov, float aspect, float zNear, float zFar)
{
    float yScale = 1.0f / tanf(fov / 2);
    float xScale = yScale / aspect;
    
    return Matrix4x4(xScale, 0.0f  , 0.0f, 0.0f,
                    0.0f  , yScale, 0.0f, 0.0f,
                    0.0f  , 0.0f  , zFar / (zNear - zFar) , -1.0f,
                    0.0f  , 0.0f  , zNear * zFar / (zNear - zFar), 0.0f);
}

Matrix4x4 Matrix4x4::Rotate(const Quaternion& q)
{
    return q.ToMatrix4x4();
}

Matrix4x4 Matrix4x4::RotationX(float rad)
{
    float c = cosf(rad);
    float s = sinf(rad);
    
    return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
                    0.0f,    c,    s, 0.0f,
                    0.0f,   -s,    c, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::RotationY(float rad)
{
    float c = cosf(rad);
    float s = sinf(rad);
    
    return Matrix4x4(   c, 0.0f,   -s, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                       s, 0.0f,    c, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::RotationZ(float rad)
{
    float c = cosf(rad);
    float s = sinf(rad);
    
    return Matrix4x4(   c,    s, 0.0f, 0.0f,
                      -s,    c, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::Scale(float x, float y)
{
    return Matrix4x4::Scale(x, y, 1.0f);
}

Matrix4x4 Matrix4x4::Scale(const Vector2& vec)
{
    return Matrix4x4::Scale(vec.x, vec.y, 1.0f);
}

Matrix4x4 Matrix4x4::Scale(float x, float y, float z)
{
    return Matrix4x4(   x, 0.0f, 0.0f, 0.0f,
                    0.0f,    y, 0.0f, 0.0f,
                    0.0f, 0.0f,    z, 0.0f,
                    0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::Scale(const Vector3& vec)
{
    return Matrix4x4(vec.x,  0.0f,  0.0f, 0.0f,
                     0.0f, vec.y,  0.0f, 0.0f,
                     0.0f,  0.0f, vec.z, 0.0f,
                     0.0f,  0.0f,  0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::Translation(float x, float y)
{
    return Matrix4x4::Translation(x, y, 0.0f);
}

Matrix4x4 Matrix4x4::Translation(const Vector2& pos)
{
    return Matrix4x4::Translation(pos.x, pos.y, 0.0f);
}

Matrix4x4 Matrix4x4::Translation(float x, float y, float z)
{
    return Matrix4x4(1.0f, 0.0f,  0.0f, 0.0f,
                     0.0f, 1.0f,  0.0f, 0.0f,
                     0.0f, 0.0f,  1.0f, 0.0f,
                     x   , y   ,  z   , 1.0f);
}

Matrix4x4 Matrix4x4::Translation(const Vector3& pos)
{
    return Matrix4x4(1.0f,  0.0f,  0.0f,  0.0f,
                     0.0f,  1.0f,  0.0f,  0.0f,
                     0.0f,  0.0f,  1.0f,  0.0f,
                     pos.x, pos.y, pos.z, 1.0f);
}

Matrix4x4 Matrix4x4::TRS(const Vector3& pos, const Quaternion& q, const Vector3& s)
{
    Matrix4x4 ret = Matrix4x4::identity;

    ret *= Translation(pos);
    ret *= Matrix4x4(q);
    ret *= Scale(s);

    return ret;
}


#pragma mark - 数値補完

Matrix4x4 Matrix4x4::EaseIn(const Matrix4x4& mat1, const Matrix4x4& mat2, float t)
{
    return mat1 + (mat2 - mat1) * (t * t);
}

Matrix4x4 Matrix4x4::EaseInOut(const Matrix4x4& mat1, const Matrix4x4& mat2, float t)
{
    Matrix4x4 middle = (mat1 + mat2) / 2;
    
    t *= 2;
    if (t <= 1.0f) {
        return mat1 + (middle - mat1) * (t * t);
    }
    t -= 1;
    return middle - (mat2 - middle) * (t * (t - 2));
}

Matrix4x4 Matrix4x4::EaseOut(const Matrix4x4& mat1, const Matrix4x4& mat2, float t)
{
    return (mat1 - (mat2 - mat1) * (t * (t - 2)));
}

Matrix4x4 Matrix4x4::Lerp(const Matrix4x4& mat1, const Matrix4x4& mat2, float t)
{
    return mat1 + (mat2 - mat1) * t;
}

Matrix4x4 Matrix4x4::SmoothStep(const Matrix4x4& mat1, const Matrix4x4& mat2, float t)
{
    return Matrix4x4(
        Mathf::SmoothStep(mat1.m00, mat2.m00, t),
        Mathf::SmoothStep(mat1.m01, mat2.m01, t),
        Mathf::SmoothStep(mat1.m02, mat2.m02, t),
        Mathf::SmoothStep(mat1.m03, mat2.m03, t),

        Mathf::SmoothStep(mat1.m10, mat2.m10, t),
        Mathf::SmoothStep(mat1.m11, mat2.m11, t),
        Mathf::SmoothStep(mat1.m12, mat2.m12, t),
        Mathf::SmoothStep(mat1.m13, mat2.m13, t),

        Mathf::SmoothStep(mat1.m20, mat2.m20, t),
        Mathf::SmoothStep(mat1.m20, mat2.m20, t),
        Mathf::SmoothStep(mat1.m20, mat2.m20, t),
        Mathf::SmoothStep(mat1.m20, mat2.m20, t),

        Mathf::SmoothStep(mat1.m30, mat2.m30, t),
        Mathf::SmoothStep(mat1.m31, mat2.m31, t),
        Mathf::SmoothStep(mat1.m32, mat2.m32, t),
        Mathf::SmoothStep(mat1.m33, mat2.m33, t));
}


#pragma mark - コンストラクタ

Matrix4x4::Matrix4x4()
{
    m00 = 0.0f;
    m01 = 0.0f;
    m02 = 0.0f;
    m03 = 0.0f;

    m10 = 0.0f;
    m11 = 0.0f;
    m12 = 0.0f;
    m13 = 0.0f;

    m20 = 0.0f;
    m21 = 0.0f;
    m22 = 0.0f;
    m23 = 0.0f;

    m30 = 0.0f;
    m31 = 0.0f;
    m32 = 0.0f;
    m33 = 0.0f;
}

Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33)
{
    this->m00 = m00;
    this->m01 = m01;
    this->m02 = m02;
    this->m03 = m03;
    
    this->m10 = m10;
    this->m11 = m11;
    this->m12 = m12;
    this->m13 = m13;
    
    this->m20 = m20;
    this->m21 = m21;
    this->m22 = m22;
    this->m23 = m23;
    
    this->m30 = m30;
    this->m31 = m31;
    this->m32 = m32;
    this->m33 = m33;
}

Matrix4x4::Matrix4x4(const Quaternion& quat)
{
    float x2 = quat.x + quat.x;
    float y2 = quat.y + quat.y;
    float z2 = quat.z + quat.z;

    float xx = quat.x * x2;
    float xy = quat.x * y2;
    float xz = quat.x * z2;
    
    float yy = quat.y * y2;
    float yz = quat.y * z2;

    float zz = quat.z * z2;
    
    float wx = quat.w * x2;
    float wy = quat.w * y2;
    float wz = quat.w * z2;
    
    m00 = 1.0f - (yy + zz);
    m01 = xy + wz;
    m02 = xz - wy;
    m03 = 0.0f;
    m10 = xy - wz;
    m11 = 1.0f - (xx + zz);
    m12 = yz + wx;
    m13 = 0.0f;
    m20 = xz + wy;
    m21 = yz - wx;
    m22 = 1.0f - (xx + yy);
    m23 = 0.0f;
    m30 = 0.0f;
    m31 = 0.0f;
    m32 = 0.0f;
    m33 = 1.0f;
}


#pragma mark - Public 関数

bool Matrix4x4::Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const
{
    translation.x = m30;
    translation.y = m31;
    translation.z = m32;

    scale.x = Vector3(m00, m01, m02).Magnitude();
    scale.y = Vector3(m10, m11, m12).Magnitude();
    scale.z = Vector3(m20, m21, m22).Magnitude();

    if (fabsf(scale.x) < 9.99999944E-11f ||
        fabsf(scale.y) < 9.99999944E-11f ||
        fabsf(scale.z) < 9.99999944E-11f)
    {
        return false;
    }

    Matrix4x4 rm(m00/scale.x, m01/scale.x, m02/scale.x, 0.0f,
                 m10/scale.y, m11/scale.y, m12/scale.y, 0.0f,
                 m20/scale.z, m21/scale.z, m22/scale.z, 0.0f,
                 0.0f       , 0.0f       , 0.0f       , 1.0f);
    rotation = rm.ToQuaternion();

    return true;
}

float Matrix4x4::Determinant() const
{
    float ret = 0.0f;

    ret += m00 * m11 * m22 * m33 + m00 * m21 * m32 * m13 + m00 * m31 * m12 * m23;
    ret += m10 * m01 * m32 * m23 + m10 * m21 * m02 * m33 + m10 * m31 * m22 * m03;
    ret += m20 * m01 * m12 * m33 + m20 * m11 * m32 * m03 + m20 * m31 * m02 * m13;
    ret += m30 * m01 * m22 * m13 + m30 * m11 * m02 * m23 + m30 * m21 * m12 * m03;

    ret += -m00 * m11 * m32 * m23 - m00 * m21 * m12 * m33 - m00 * m31 * m22 * m13;
    ret += -m10 * m01 * m22 * m33 - m10 * m21 * m32 * m03 - m10 * m31 * m02 * m23;
    ret += -m20 * m01 * m32 * m13 - m20 * m11 * m02 * m33 - m20 * m31 * m12 * m03;
    ret += -m30 * m01 * m12 * m23 - m30 * m11 * m22 * m03 - m30 * m21 * m02 * m13;

    return ret;
}

Matrix4x4 Matrix4x4::Inverse() const
{
    float det = Determinant();
    if (det == 0.0f) {
        AbortGame("Matrix4x4::Inverse() determinant should not be zero.");
    }

    Matrix4x4 ret;

    ret.m00 = (m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31) / det;
    ret.m01 = (m01*m23*m32 + m02*m21*m33 + m03*m22*m31 - m01*m22*m33 - m02*m23*m31 - m03*m21*m32) / det;
    ret.m02 = (m01*m12*m33 + m02*m13*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 - m03*m12*m31) / det;
    ret.m03 = (m01*m13*m22 + m02*m11*m23 + m03*m12*m21 - m01*m12*m23 - m02*m13*m21 - m03*m11*m22) / det;

    ret.m10 = (m10*m23*m32 + m12*m20*m33 + m13*m22*m30 - m10*m22*m33 - m12*m23*m30 - m13*m20*m32) / det;
    ret.m11 = (m00*m22*m33 + m02*m23*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 - m03*m22*m30) / det;
    ret.m12 = (m00*m13*m32 + m02*m10*m33 + m03*m12*m30 - m00*m12*m33 - m02*m13*m30 - m03*m10*m32) / det;
    ret.m13 = (m00*m12*m23 + m02*m13*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 - m03*m12*m20) / det;

    ret.m20 = (m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 - m13*m21*m30) / det;
    ret.m21 = (m00*m23*m31 + m01*m20*m33 + m03*m21*m30 - m00*m21*m33 - m01*m23*m30 - m03*m20*m31) / det;
    ret.m22 = (m00*m11*m33 + m01*m13*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 - m03*m11*m30) / det;
    ret.m23 = (m00*m13*m21 + m01*m10*m23 + m03*m11*m20 - m00*m11*m23 - m01*m13*m20 - m03*m10*m21) / det;

    ret.m30 = (m10*m22*m31 + m11*m20*m32 + m12*m21*m30 - m10*m21*m32 - m11*m22*m30 - m12*m20*m31) / det;
    ret.m31 = (m00*m21*m32 + m01*m22*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 - m02*m21*m30) / det;
    ret.m32 = (m00*m12*m31 + m01*m10*m32 + m02*m11*m30 - m00*m11*m32 - m01*m12*m30 - m02*m10*m31) / det;
    ret.m33 = (m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 - m02*m11*m20) / det;

    return ret;
}

Quaternion Matrix4x4::ToQuaternion() const
{
    return Quaternion(*this);
}

Matrix4x4 Matrix4x4::Transpose() const
{
    Matrix4x4 ret;

    ret.m00 = m00;
    ret.m01 = m10;
    ret.m02 = m20;
    ret.m03 = m30;

    ret.m10 = m01;
    ret.m11 = m11;
    ret.m12 = m21;
    ret.m13 = m31;

    ret.m20 = m02;
    ret.m21 = m12;
    ret.m22 = m22;
    ret.m23 = m32;

    ret.m30 = m03;
    ret.m31 = m13;
    ret.m32 = m23;
    ret.m33 = m33;

    return ret;
}

std::string Matrix4x4::ToString() const
{
    return ToString("%.5f");
}

std::string Matrix4x4::ToString(const std::string& format) const
{
    std::string m00Str = FormatString(format.c_str(), m00);
    std::string m01Str = FormatString(format.c_str(), m01);
    std::string m02Str = FormatString(format.c_str(), m02);
    std::string m03Str = FormatString(format.c_str(), m03);
    std::string m10Str = FormatString(format.c_str(), m10);
    std::string m11Str = FormatString(format.c_str(), m11);
    std::string m12Str = FormatString(format.c_str(), m12);
    std::string m13Str = FormatString(format.c_str(), m13);
    std::string m20Str = FormatString(format.c_str(), m20);
    std::string m21Str = FormatString(format.c_str(), m21);
    std::string m22Str = FormatString(format.c_str(), m22);
    std::string m23Str = FormatString(format.c_str(), m23);
    std::string m30Str = FormatString(format.c_str(), m30);
    std::string m31Str = FormatString(format.c_str(), m31);
    std::string m32Str = FormatString(format.c_str(), m32);
    std::string m33Str = FormatString(format.c_str(), m33);
    return FormatString("%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n%s\t%s\t%s\t%s\n",
                         m00Str.c_str(),
                         m01Str.c_str(),
                         m02Str.c_str(),
                         m03Str.c_str(),
                         m10Str.c_str(),
                         m11Str.c_str(),
                         m12Str.c_str(),
                         m13Str.c_str(),
                         m20Str.c_str(),
                         m21Str.c_str(),
                         m22Str.c_str(),
                         m23Str.c_str(),
                         m30Str.c_str(),
                         m31Str.c_str(),
                         m32Str.c_str(),
                         m33Str.c_str());
}

const char* Matrix4x4::c_str() const
{
    return GMObject::c_str();
}

const char* Matrix4x4::c_str(const std::string& format) const
{
    return ToString(format).c_str();
}


#pragma mark - 演算子のオーバーロード

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& matrix)
{
    m00 = matrix.m00;
    m01 = matrix.m01;
    m02 = matrix.m02;
    m03 = matrix.m03;

    m10 = matrix.m10;
    m11 = matrix.m11;
    m12 = matrix.m12;
    m13 = matrix.m13;

    m20 = matrix.m20;
    m21 = matrix.m21;
    m22 = matrix.m22;
    m23 = matrix.m23;

    m30 = matrix.m30;
    m31 = matrix.m31;
    m32 = matrix.m32;
    m33 = matrix.m33;

    return *this;
}

Matrix4x4 Matrix4x4::operator-() const
{
    return (*this) * -1;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& matrix) const
{
    Matrix4x4 ret(*this);

    ret.m00 += matrix.m00;
    ret.m01 += matrix.m01;
    ret.m02 += matrix.m02;
    ret.m03 += matrix.m03;
    
    ret.m10 += matrix.m10;
    ret.m11 += matrix.m11;
    ret.m12 += matrix.m12;
    ret.m13 += matrix.m13;
    
    ret.m20 += matrix.m20;
    ret.m21 += matrix.m21;
    ret.m22 += matrix.m22;
    ret.m23 += matrix.m23;
    
    ret.m30 += matrix.m30;
    ret.m31 += matrix.m31;
    ret.m32 += matrix.m32;
    ret.m33 += matrix.m33;
    
    return ret;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& matrix) const
{
    Matrix4x4 ret(*this);

    ret.m00 -= matrix.m00;
    ret.m01 -= matrix.m01;
    ret.m02 -= matrix.m02;
    ret.m03 -= matrix.m03;
    
    ret.m10 -= matrix.m10;
    ret.m11 -= matrix.m11;
    ret.m12 -= matrix.m12;
    ret.m13 -= matrix.m13;
    
    ret.m20 -= matrix.m20;
    ret.m21 -= matrix.m21;
    ret.m22 -= matrix.m22;
    ret.m23 -= matrix.m23;
    
    ret.m30 -= matrix.m30;
    ret.m31 -= matrix.m31;
    ret.m32 -= matrix.m32;
    ret.m33 -= matrix.m33;
    
    return ret;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& matrix) const
{
    Matrix4x4& a = const_cast<Matrix4x4&>(matrix);
    Matrix4x4& b = const_cast<Matrix4x4&>(*this);
    
    Matrix4x4 ret;

    ret.m00 = a.m00 * b.m00 + a.m10 * b.m01 + a.m20 * b.m02 + a.m30 * b.m03;
    ret.m01 = a.m01 * b.m00 + a.m11 * b.m01 + a.m21 * b.m02 + a.m31 * b.m03;
    ret.m02 = a.m02 * b.m00 + a.m12 * b.m01 + a.m22 * b.m02 + a.m32 * b.m03;
    ret.m03 = a.m03 * b.m00 + a.m13 * b.m01 + a.m23 * b.m02 + a.m33 * b.m03;
    
    ret.m10 = a.m00 * b.m10 + a.m10 * b.m11 + a.m20 * b.m12 + a.m30 * b.m13;
    ret.m11 = a.m01 * b.m10 + a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
    ret.m12 = a.m02 * b.m10 + a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
    ret.m13 = a.m03 * b.m10 + a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
    
    ret.m20 = a.m00 * b.m20 + a.m10 * b.m21 + a.m20 * b.m22 + a.m30 * b.m23;
    ret.m21 = a.m01 * b.m20 + a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
    ret.m22 = a.m02 * b.m20 + a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
    ret.m23 = a.m03 * b.m20 + a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
    
    ret.m30 = a.m00 * b.m30 + a.m10 * b.m31 + a.m20 * b.m32 + a.m30 * b.m33;
    ret.m31 = a.m01 * b.m30 + a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;
    ret.m32 = a.m02 * b.m30 + a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;
    ret.m33 = a.m03 * b.m30 + a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;
    
    return ret;
}

Matrix4x4 Matrix4x4::operator/(const Matrix4x4& matrix) const
{
    Matrix4x4 ret(*this);

    ret.m00 /= matrix.m00;
    ret.m01 /= matrix.m01;
    ret.m02 /= matrix.m02;
    ret.m03 /= matrix.m03;
    
    ret.m10 /= matrix.m10;
    ret.m11 /= matrix.m11;
    ret.m12 /= matrix.m12;
    ret.m13 /= matrix.m13;
    
    ret.m20 /= matrix.m20;
    ret.m21 /= matrix.m21;
    ret.m22 /= matrix.m22;
    ret.m23 /= matrix.m23;
    
    ret.m30 /= matrix.m30;
    ret.m31 /= matrix.m31;
    ret.m32 /= matrix.m32;
    ret.m33 /= matrix.m33;
    
    return ret;    
}

Matrix4x4 Matrix4x4::operator*(float value) const
{
    Matrix4x4 ret(*this);

    ret.m00 *= value;
    ret.m01 *= value;
    ret.m02 *= value;
    ret.m03 *= value;
    
    ret.m10 *= value;
    ret.m11 *= value;
    ret.m12 *= value;
    ret.m13 *= value;
    
    ret.m20 *= value;
    ret.m21 *= value;
    ret.m22 *= value;
    ret.m23 *= value;
    
    ret.m30 *= value;
    ret.m31 *= value;
    ret.m32 *= value;
    ret.m33 *= value;
    
    return ret;
}

Vector2 Matrix4x4::operator*(const Vector2& vector) const
{
    Vector4 v4 = *this * Vector4(vector, 0.0f, 1.0f);
    return Vector2(v4.x, v4.y);
}

Vector3 Matrix4x4::operator*(const Vector3& vector) const
{
    Vector4 v4 = *this * Vector4(vector, 1.0f);
    return Vector3(v4.x, v4.y, v4.z);
}

Vector4 Matrix4x4::operator*(const Vector4& vector) const
{
    Vector4 ret;

    ret.x = vector.x * m00 + vector.y * m10 + vector.z * m20 + vector.w * m30;
    ret.y = vector.x * m01 + vector.y * m11 + vector.z * m21 + vector.w * m31;
    ret.z = vector.x * m02 + vector.y * m12 + vector.z * m22 + vector.w * m32;
    ret.w = vector.x * m03 + vector.y * m13 + vector.z * m23 + vector.w * m33;
    
    return ret;
}

Matrix4x4 Matrix4x4::operator/(float value) const
{
    Matrix4x4 ret(*this);

    ret.m00 /= value;
    ret.m01 /= value;
    ret.m02 /= value;
    ret.m03 /= value;
    
    ret.m10 /= value;
    ret.m11 /= value;
    ret.m12 /= value;
    ret.m13 /= value;
    
    ret.m20 /= value;
    ret.m21 /= value;
    ret.m22 /= value;
    ret.m23 /= value;
    
    ret.m30 /= value;
    ret.m31 /= value;
    ret.m32 /= value;
    ret.m33 /= value;
    
    return ret;
}

Matrix4x4 operator*(float value, const Matrix4x4& matrix)
{
    Matrix4x4 ret(matrix);

    ret.m00 *= value;
    ret.m01 *= value;
    ret.m02 *= value;
    ret.m03 *= value;
    
    ret.m10 *= value;
    ret.m11 *= value;
    ret.m12 *= value;
    ret.m13 *= value;
    
    ret.m20 *= value;
    ret.m21 *= value;
    ret.m22 *= value;
    ret.m23 *= value;
    
    ret.m30 *= value;
    ret.m31 *= value;
    ret.m32 *= value;
    ret.m33 *= value;
    
    return ret;
}

Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& matrix)
{
    m00 += matrix.m00;
    m01 += matrix.m01;
    m02 += matrix.m02;
    m03 += matrix.m03;
    
    m10 += matrix.m10;
    m11 += matrix.m11;
    m12 += matrix.m12;
    m13 += matrix.m13;
    
    m20 += matrix.m20;
    m21 += matrix.m21;
    m22 += matrix.m22;
    m23 += matrix.m23;
    
    m30 += matrix.m30;
    m31 += matrix.m31;
    m32 += matrix.m32;
    m33 += matrix.m33;

    return *this;
}

Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& matrix)
{
    m00 -= matrix.m00;
    m01 -= matrix.m01;
    m02 -= matrix.m02;
    m03 -= matrix.m03;
    
    m10 -= matrix.m10;
    m11 -= matrix.m11;
    m12 -= matrix.m12;
    m13 -= matrix.m13;
    
    m20 -= matrix.m20;
    m21 -= matrix.m21;
    m22 -= matrix.m22;
    m23 -= matrix.m23;
    
    m30 -= matrix.m30;
    m31 -= matrix.m31;
    m32 -= matrix.m32;
    m33 -= matrix.m33;

    return *this;
}

Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& matrix)
{
    *this = (*this) * matrix;
    return *this;
}

Matrix4x4& Matrix4x4::operator/=(const Matrix4x4& matrix)
{
    m00 /= matrix.m00;
    m01 /= matrix.m01;
    m02 /= matrix.m02;
    m03 /= matrix.m03;

    m10 /= matrix.m10;
    m11 /= matrix.m11;
    m12 /= matrix.m12;
    m13 /= matrix.m13;

    m20 /= matrix.m20;
    m21 /= matrix.m21;
    m22 /= matrix.m22;
    m23 /= matrix.m23;
    
    m30 /= matrix.m30;
    m31 /= matrix.m31;
    m32 /= matrix.m32;
    m33 /= matrix.m33;

    return *this;
}

Matrix4x4& Matrix4x4::operator*=(float value)
{
    m00 *= value;
    m01 *= value;
    m02 *= value;
    m03 *= value;
    
    m10 *= value;
    m11 *= value;
    m12 *= value;
    m13 *= value;
    
    m20 *= value;
    m21 *= value;
    m22 *= value;
    m23 *= value;
    
    m30 *= value;
    m31 *= value;
    m32 *= value;
    m33 *= value;

    return *this;
}

Matrix4x4& Matrix4x4::operator/=(float value)
{
    m00 /= value;
    m01 /= value;
    m02 /= value;
    m03 /= value;
    
    m10 /= value;
    m11 /= value;
    m12 /= value;
    m13 /= value;
    
    m20 /= value;
    m21 /= value;
    m22 /= value;
    m23 /= value;
    
    m30 /= value;
    m31 /= value;
    m32 /= value;
    m33 /= value;

    return *this;
}

bool Matrix4x4::operator==(const Matrix4x4& matrix) const
{
    if (fabsf(m00 - matrix.m00) >= 9.99999944E-11f) return false;
    if (fabsf(m01 - matrix.m01) >= 9.99999944E-11f) return false;
    if (fabsf(m02 - matrix.m02) >= 9.99999944E-11f) return false;
    if (fabsf(m03 - matrix.m03) >= 9.99999944E-11f) return false;
    
    if (fabsf(m10 - matrix.m10) >= 9.99999944E-11f) return false;
    if (fabsf(m11 - matrix.m11) >= 9.99999944E-11f) return false;
    if (fabsf(m12 - matrix.m12) >= 9.99999944E-11f) return false;
    if (fabsf(m13 - matrix.m13) >= 9.99999944E-11f) return false;
    
    if (fabsf(m20 - matrix.m20) >= 9.99999944E-11f) return false;
    if (fabsf(m21 - matrix.m21) >= 9.99999944E-11f) return false;
    if (fabsf(m22 - matrix.m22) >= 9.99999944E-11f) return false;
    if (fabsf(m23 - matrix.m23) >= 9.99999944E-11f) return false;

    if (fabsf(m30 - matrix.m30) >= 9.99999944E-11f) return false;
    if (fabsf(m31 - matrix.m31) >= 9.99999944E-11f) return false;
    if (fabsf(m32 - matrix.m32) >= 9.99999944E-11f) return false;
    if (fabsf(m33 - matrix.m33) >= 9.99999944E-11f) return false;
    
    return true;
}

bool Matrix4x4::operator!=(const Matrix4x4& matrix) const
{
    if (fabsf(m00 - matrix.m00) >= 9.99999944E-11f) return true;
    if (fabsf(m01 - matrix.m01) >= 9.99999944E-11f) return true;
    if (fabsf(m02 - matrix.m02) >= 9.99999944E-11f) return true;
    if (fabsf(m03 - matrix.m03) >= 9.99999944E-11f) return true;
    
    if (fabsf(m10 - matrix.m10) >= 9.99999944E-11f) return true;
    if (fabsf(m11 - matrix.m11) >= 9.99999944E-11f) return true;
    if (fabsf(m12 - matrix.m12) >= 9.99999944E-11f) return true;
    if (fabsf(m13 - matrix.m13) >= 9.99999944E-11f) return true;
    
    if (fabsf(m20 - matrix.m20) >= 9.99999944E-11f) return true;
    if (fabsf(m21 - matrix.m21) >= 9.99999944E-11f) return true;
    if (fabsf(m22 - matrix.m22) >= 9.99999944E-11f) return true;
    if (fabsf(m23 - matrix.m23) >= 9.99999944E-11f) return true;
    
    if (fabsf(m30 - matrix.m30) >= 9.99999944E-11f) return true;
    if (fabsf(m31 - matrix.m31) >= 9.99999944E-11f) return true;
    if (fabsf(m32 - matrix.m32) >= 9.99999944E-11f) return true;
    if (fabsf(m33 - matrix.m33) >= 9.99999944E-11f) return true;
    
    return false;
}


#pragma mark - 内部実装に使用する関数群

void Matrix4x4::SetBackward(const Vector3& vec)
{
    m20 = vec.x;
    m21 = vec.y;
    m22 = vec.z;
}

void Matrix4x4::SetDown(const Vector3& vec)
{
    m10 = -vec.x;
    m11 = -vec.y;
    m12 = -vec.z;
}

void Matrix4x4::SetForward(const Vector3& vec)
{
    m20 = -vec.x;
    m21 = -vec.y;
    m22 = -vec.z;
}

void Matrix4x4::SetLeft(const Vector3& vec)
{
    m00 = -vec.x;
    m01 = -vec.y;
    m02 = -vec.z;
}

void Matrix4x4::SetRight(const Vector3& vec)
{
    m00 = vec.x;
    m01 = vec.y;
    m02 = vec.z;
}

void Matrix4x4::SetTranslation(const Vector3& vec)
{
    m30 = vec.x;
    m31 = vec.y;
    m32 = vec.z;
}

void Matrix4x4::SetUp(const Vector3& vec)
{
    m10 = vec.x;
    m11 = vec.y;
    m12 = vec.z;
}

