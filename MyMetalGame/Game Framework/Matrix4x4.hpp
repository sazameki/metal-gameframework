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
            /// m00要素
            float m00;

            /// m01要素
            float m01;

            /// m02要素
            float m02;

            /// m03要素
            float m03;
            
            /// m10要素
            float m10;
            
            /// m11要素
            float m11;
            
            /// m12要素
            float m12;
            
            /// m13要素
            float m13;

            /// m20要素
            float m20;
            
            /// m21要素
            float m21;

            /// m22要素
            float m22;
            
            /// m23要素
            float m23;
            
            /// m30要素
            float m30;

            /// m31要素
            float m31;

            /// m32要素
            float m32;

            /// m33要素
            float m33;
        };
    };


#pragma mark - Static 関数

    /// 指定された位置のオブジェクトの周囲を回転するビルボードを表す4x4行列を作成します。
    static Matrix4x4    Billboard(const Vector3& objectPos, const Vector3& cameraPos, const Vector3& cameraUpVec);
    
    /// 指定された軸の周りを回転する円筒状のビルボードを表す4x4行列を作成します。
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
    
    /// 直交射影行列を作成します。
    static Matrix4x4    Ortho(float left, float right, float bottom, float top, float zNear, float zFar);
    
    /// 透視投影行列を作成します。
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

    /// この行列に行列matrixの内容をコピーします。
    Matrix4x4&  operator=(const Matrix4x4& matrix);
    
    /// この行列の各要素に-1を掛けた行列を作成します。
    Matrix4x4   operator-() const;

    /// この行列の各要素に、与えられた行列の同じ要素を足し合わせた行列を作成します。
    Matrix4x4   operator+(const Matrix4x4& matrix) const;

    /// この行列の各要素から、与えられた行列の同じ要素を引いた行列を作成します。
    Matrix4x4   operator-(const Matrix4x4& matrix) const;

    /// この行列に、与えられた行列を掛けた行列を作成します。
    Matrix4x4   operator*(const Matrix4x4& matrix) const;

    /// この行列の各要素を、与えられた行列の同じ要素で割った行列を作成します。
    Matrix4x4   operator/(const Matrix4x4& matrix) const;

    /// この行列の各要素に、与えられたスカラ値valueを掛けた行列を作成します。
    Matrix4x4   operator*(float value) const;

    /// Vector2をこの行列で変換したVector2を作成します。
    Vector2     operator*(const Vector2& vector) const;

    /// Vector3をこの行列で変換したVector3を作成します。
    Vector3     operator*(const Vector3& vector) const;

    /// Vector4をこの行列で変換したVector4を作成します。
    Vector4     operator*(const Vector4& vector) const;

    /// この行列の各要素を、与えられたスカラ値valueで割った行列を作成します。
    Matrix4x4   operator/(float value) const;

    /// スカラ値を行列の各要素に掛け合わせた行列を作成します。
    friend Matrix4x4 operator*(float value, const Matrix4x4& matrix);

    /// この行列の各要素に、与えられた行列の同じ要素を足し合わせます。
    Matrix4x4&   operator+=(const Matrix4x4& matrix);
    
    /// この行列の各要素から、与えられた行列の同じ要素を引きます。
    Matrix4x4&   operator-=(const Matrix4x4& matrix);
    
    /// この行列に、与えられた行列を掛け合わせます。
    Matrix4x4&   operator*=(const Matrix4x4& matrix);
    
    /// この行列の各要素を、与えられた行列の同じ要素で割ります。
    Matrix4x4&   operator/=(const Matrix4x4& matrix);
    
    /// この行列の各要素に、スカラ値valueを掛け合わせます。
    Matrix4x4&   operator*=(float value);
    
    /// この行列の各要素を、スカラ値valueで割ります。
    Matrix4x4&   operator/=(float value);
    
    /// 与えられた行列がこの行列と等しいかを判定します。
    bool        operator==(const Matrix4x4& matrix) const;
    
    /// 与えられた行列がこの行列と等しくないかを判定します。
    bool        operator!=(const Matrix4x4& matrix) const;


#pragma mark - 内部実装に使用する関数群
private:

    /// m20,m21,m22の要素に、与えられたベクトルの値をセットします。
    void    SetBackward(const Vector3& vec);

    /// m10,m11,m12の要素に、与えられたベクトルの値を反転してセットします。
    void    SetDown(const Vector3& vec);

    /// m20,m21,m22の要素に、与えられたベクトルの値を反転してセットします。
    void    SetForward(const Vector3& vec);

    /// m00,m01,m02の要素に、与えられたベクトルの値を反転してセットします。
    void    SetLeft(const Vector3& vec);

    /// m00,m01,m02の要素に、与えられたベクトルの値をセットします。
    void    SetRight(const Vector3& vec);

    /// m30,m31,m32の要素に、与えられたベクトルの値をセットします。
    void    SetTranslation(const Vector3& vec);

    /// m10,m11,m12の要素に、与えられたベクトルの値をセットします。
    void    SetUp(const Vector3& vec);

};


#endif  //#ifndef __MATRIX4X4_HPP__


