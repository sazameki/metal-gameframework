//
//  Matrix4x4.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
//

#ifndef __MATRIX4X4_HPP__
#define __MATRIX4X4_HPP__


#include "GMObject.hpp"

struct Matrix4x4;
struct GMPlane;
struct Quaternion;
struct Vector2;
struct Vector3;
struct Vector4;


/// 4x4の変換行列を表す構造体です。
struct Matrix4x4 : public GMObject
{

#pragma mark - Static 変数

    /// 単位行列を表す定数
    static const Matrix4x4&  identity;

    /// 要素がすべてゼロの行列を表す定数
    static const Matrix4x4&  zero;


#pragma mark - Public 変数

    union {
        float   mat[16];
        struct {
            /*!
                @var m00
             */
            float m00;

            /*!
                @var m01
             */
            float m01;

            /*!
                @var m02
             */
            float m02;

            /*!
                @var m03
             */
            float m03;
            
            /*!
                @var m10
             */
            float m10;
            
            /*!
                @var m11
             */
            float m11;
            
            /*!
                @var m12
            */
            float m12;
            
            /*!
                @var m13
             */
            float m13;

            /*!
                @var m20
             */
            float m20;
            
            /*!
                @var m21
             */
            float m21;

            /*!
                @var m22
             */
            float m22;
            
            /*!
                @var m23
             */
            float m23;
            
            /*!
                @var m30
             */
            float m30;

            /*!
                @var m31
             */
            float m31;

            /*!
                @var m32
             */
            float m32;

            /*!
                @var m33
             */
            float m33;
        };
    };


#pragma mark - Static 関数

    /*!
        Billboard
     */
    static Matrix4x4    Billboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& cameraUpVec);
    
    /*!
        ConstrainedBillboard
     */
    static Matrix4x4    ConstrainedBillboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& rotateAxis,
                                             const Vector3& cameraForwardVec, const Vector3& objectForwardVec);

    /// 2つの行列間で、Ease-In補間を計算します。
    static Matrix4x4    EaseIn(const Matrix4x4& mat1, const Matrix4x4& mat2, float t);

    /// 2つの行列間で、Ease-In-Out補間を計算します。
    static Matrix4x4    EaseInOut(const Matrix4x4& mat1, const Matrix4x4& mat2, float t);

    /// 2つの行列間で、Ease-Out補間を計算します。
    static Matrix4x4    EaseOut(const Matrix4x4& mat1, const Matrix4x4& mat2, float t);

    /// 2つの行列間で、線形補間を計算します。
    static Matrix4x4    Lerp(const Matrix4x4& mat1, const Matrix4x4& mat2, float t);

    /// LookAt行列を作成します。
    static Matrix4x4    LookAt(const Vector3& from, const Vector3& to, const Vector3& up);
    
    /*!
        Ortho
     */
    static Matrix4x4    Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    
    /*!
        Perspective
     */
    static Matrix4x4    Perspective(float fov, float aspect, float zNear, float zFar);

    /// クォータニオンから、回転を表す4x4行列を作成します。
    static Matrix4x4    Rotate(const Quaternion& q);

    /// X軸を中心としたradラジアンの回転を表す4x4行列を作成します。
    static Matrix4x4    RotationX(float rad);
    
    /// Y軸を中心としたradラジアンの回転を表す4x4行列を作成します。
    static Matrix4x4    RotationY(float rad);
    
    /// Z軸を中心としたradラジアンの回転を表す4x4行列を作成します。
    static Matrix4x4    RotationZ(float rad);

    /// スケーリングを表す4x4行列を作成します。
    static Matrix4x4    Scale(float x, float y);

    /// スケーリングを表す4x4行列を作成します。
    static Matrix4x4    Scale(const Vector2& vec);

    /// スケーリングを表す4x4行列を作成します。
    static Matrix4x4    Scale(float x, float y, float z);
    
    /// スケーリングを表す4x4行列を作成します。
    static Matrix4x4    Scale(const Vector3& vec);

    /// 2つの行列間で、SmoothStep補完を計算します。
    static Matrix4x4    SmoothStep(const Matrix4x4& mat1, const Matrix4x4& mat2, float t);

    /// 平行移動を表す4x4行列を作成します。
    static Matrix4x4    Translation(float x, float y);

    /// 平行移動を表す4x4行列を作成します。
    static Matrix4x4    Translation(const Vector2& pos);

    /// 平行移動を表す4x4行列を作成します。
    static Matrix4x4    Translation(float x, float y, float z);

    /// 平行移動を表す4x4行列を作成します。
    static Matrix4x4    Translation(const Vector3& pos);

    /// 平行移動、回転、スケーリングを同時に表す4x4行列を作成します。
    static Matrix4x4    TRS(const Vector3& pos, const Quaternion& q, const Vector3& s);


#pragma mark - コンストラクタ

    /// コンストラクタ。すべての要素が 0.0 の行列を生成します。
    Matrix4x4();

    /// コンストラクタ。各要素を設定して行列を生成します。
    Matrix4x4(float m00, float m01, float m02, float m03,
              float m10, float m11, float m12, float m13,
              float m20, float m21, float m22, float m23,
              float m30, float m31, float m32, float m33);

    /// コンストラクタ。各要素をコピーして行列を生成します。
    Matrix4x4(const Quaternion& quat);


#pragma mark - Public 関数

    /// この4x4行列が表すスケール、回転、平行移動の成分を取り出します。
    bool        Decompose(Vector3& scale, Quaternion& rotation, Vector3& translation) const;

    /// 行列式を計算します。
    float       Determinant() const;
    
    /// 逆行列を計算します。
    Matrix4x4   Inverse() const;

    /// この4x4行列が表すのと同等の回転を表すクォータニオンを作成します。
    Quaternion  ToQuaternion() const;
    
    /// この行列の転置行列を作成します。
    Matrix4x4   Transpose() const;

    /// 行列の各要素を見やすくフォーマットした文字列を返します。
    std::string ToString() const override;

    /// 各要素に対して適用される書式を指定して、行列の各要素を見やすくフォーマットした文字列を返します。
    std::string ToString(const std::string& format) const;

    /// 行列の各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str() const override;

    /// 各要素に対して適用される書式を指定して、行列の各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str(const std::string& format) const;


#pragma mark - 演算子のオーバーロード

    /*!
        operator=
     */
    Matrix4x4&  operator=(const Matrix4x4& matrix);
    
    /*!
        operator-
     */
    Matrix4x4   operator-() const;

    /*!
        operator+
     */
    Matrix4x4   operator+(const Matrix4x4& matrix) const;

    /*!
        operator-
     */
    Matrix4x4   operator-(const Matrix4x4& matrix) const;

    /*!
        operator*
     */
    Matrix4x4   operator*(const Matrix4x4& matrix) const;

    /*!
        operator/
     */
    Matrix4x4   operator/(const Matrix4x4& matrix) const;

    /*!
        operator*
     */
    Matrix4x4   operator*(float value) const;

    /*!
        operator*
     */
    Vector2     operator*(const Vector2& vector) const;

    /*!
        operator*
     */
    Vector3     operator*(const Vector3& vector) const;

    /*!
        operator*
     */
    Vector4     operator*(const Vector4& vector) const;

    /*!
        operator/
     */
    Matrix4x4   operator/(float value) const;
    
    
    friend Matrix4x4 operator*(float value, const Matrix4x4& matrix);
    
    
    /*!
        operator+=
     */
    Matrix4x4&   operator+=(const Matrix4x4& matrix);
    
    /*!
        operator-=
     */
    Matrix4x4&   operator-=(const Matrix4x4& matrix);
    
    /*!
        operator*=
     */
    Matrix4x4&   operator*=(const Matrix4x4& matrix);
    
    /*!
        operator/=
     */
    Matrix4x4&   operator/=(const Matrix4x4& matrix);
    
    /*!
        operator*=
     */
    Matrix4x4&   operator*=(float value);
    
    /*!
        operator/=
     */
    Matrix4x4&   operator/=(float value);
    
    
    /*!
        operator==
     */
    bool        operator==(const Matrix4x4& matrix) const;
    
    /*!
        operator!=
     */
    bool        operator!=(const Matrix4x4& matrix) const;

#pragma mark - 内部実装に使用する関数群
private:

    void    SetBackward(const Vector3& vec);
    void    SetDown(const Vector3& vec);
    void    SetForward(const Vector3& vec);
    void    SetLeft(const Vector3& vec);
    void    SetRight(const Vector3& vec);
    void    SetTranslation(const Vector3& vec);
    void    SetUp(const Vector3& vec);

};


#endif  //#ifndef __MATRIX4X4_HPP__


