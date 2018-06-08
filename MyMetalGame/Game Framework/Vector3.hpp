//
//  Vector3.hpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __VECTOR3_HPP__
#define __VECTOR3_HPP__


#include "GMObject.hpp"
struct Vector2;
struct Matrix4x4;
struct Quaternion;


/// 3次元ベクトルを表す構造体です。
struct Vector3 : public GMObject
{
public:
    /*!
        @const  back
        @unity-compatible   true
     */
    static const Vector3&    back;

    /*!
        @const  down
        @unity-compatible   true
     */
    static const Vector3&    down;
    
    /*!
        @const  forward
        @unity-compatible   true
     */
    static const Vector3&    forward;
    
    /*!
        @const  left
        @unity-compatible   true
     */
    static const Vector3&    left;
    
    /*!
        @const  one
        @unity-compatible   true
     */
    static const Vector3&    one;
    
    /*!
        @const  right
        @unity-compatible   true
     */
    static const Vector3&    right;
    
    /*!
        @const  up
        @unity-compatible   true
     */
    static const Vector3&    up;
    
    /*!
        @const  zero
        @unity-compatible   true
     */
    static const Vector3&    zero;

public:
    /*!
        @task   Static 関数
     */

    /// from と to の2点間の角度を返します。
    static float    Angle(const Vector3& from, const Vector3& to);

    /// 大きさを maxLength までに制限した vector のコピーを返します。
    static Vector3  ClampMagnitude(const Vector3& vector, float maxLength);

    /// 2つのベクトルの外積を計算します。
    static Vector3  Cross(const Vector3 &lhs, const Vector3 &rhs);

    /*!
        Distance
        @unity-compatible   true
        2つのベクトル間の距離を返します。
     */
    static float    Distance(const Vector3& a, const Vector3& b);

    /*!
        Dot
        @unity-compatible   true
        2つのベクトルの内積を返します。
     */
    static float    Dot(const Vector3& lhs, const Vector3& rhs);

    /*!
        EaseIn
     */
    static Vector3  EaseIn(const Vector3& a, const Vector3& b, float t);

    /*!
        EaseInOut
     */
    static Vector3  EaseInOut(const Vector3& a, const Vector3& b, float t);

    /*!
        EaseOut
     */
    static Vector3  EaseOut(const Vector3& a, const Vector3& b, float t);

    /*!
        Lerp
        @unity-compatible   true
        2つのベクトル間を線形補間します。
        パラメーター t は[0, 1]の範囲に制限されます。
     */
    static Vector3  Lerp(const Vector3& a, const Vector3& b, float t);

    /*!
        LerpUnclamped
        @unity-compatible   true
        2つのベクトル間を線形補間します。
        パラメーター t の範囲は制限されません。
     */
    static Vector3  LerpUnclamped(const Vector3& a, const Vector3& b, float t);

    /*!
        Max
        @unity-compatible   true
        2つのベクトルの各成分の最大の要素からなるベクトルを返します。
     */
    static Vector3  Max(const Vector3& a, const Vector3& b);

    /*!
        Min
        @unity-compatible   true
        2つのベクトルの各成分の最小の要素からなるベクトルを返します。
     */
    static Vector3  Min(const Vector3& a, const Vector3& b);

    /*!
        MoveTowards
        @unity-compatible   true
        現在の位置 current から target に向けて移動します。
     */
    static Vector3  MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);

    /*!
        OrthoNormalize
        @unity-compatible   true (unsupported)
     */
    //static void     OrthoNormalize(Vector3& normal, Vector3& tangent);

    /*!
        OrthoNormalize
        @unity-compatible   true (unsupported)
     */
    //static void     OrthoNormalize(Vector3& normal, Vector3& tangent, Vector3& binormal);

    /*!
        Reflect
        @unity-compatible   true
        法線で定義された平面でベクトルを反射します。
     */
    static Vector3  Reflect(const Vector3 &inDirection, const Vector3 &inNormal);

    /*!
        RotateTowards
        @unity-compatible   true (unsupported)
     */
    //static Vector3  RotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);

    /*!
        Scale
        @unity-compatible   true
        2つのベクトルの各成分を乗算します。
     */
    static Vector3  Scale(const Vector3& a, const Vector3& b);

    /*!
        Slerp
        @unity-compatible   true
     */
    static Vector3  Slerp(const Vector3& a, const Vector3& b, float t);

    /*!
        SlerpUnclamped
        @unity-compatible   true
     */
    static Vector3  SlerpUnclamped(const Vector3& a, const Vector3& b, float t);

    /*!
        SmoothDamp
        @unity-compatible   true
     */
    static Vector3  SmoothDamp(const Vector3 &current, const Vector3 &target, Vector3 &currentVelocity,
                               float smoothTime, float maxSpeed, float deltaTime);

    static Vector3 SmoothStep(const Vector3& a, const Vector3& b, float t);

    
    /*!
        @var    x
        @unity-compatible   true
     */
    float x;
    
    /*!
        @var    y
        @unity-compatible   true
     */
    float y;
    
    /*!
        @var    z
        @unity-compatible   true
     */
    float z;
    
public:
    /*!
        @task   コンストラクタ
     */

    /*!
        Vector3
        @unity-compatible   false
     */
    Vector3();

    /*!
        Vector3
        @unity-compatible   true
     */
    Vector3(float x, float y, float z);
    
    /*!
        Vector3
        @unity-compatible   false
     */
    Vector3(const Vector2& vec, float z);
    
    /*!
        Vector3
        @unity-compatible   false
     */
    Vector3(const Vector3& vec);

    
public:
    /*!
        @task   Public 関数
     */
    
    /*!
        Magnitude
        @unity-compatible   true
        ベクトルの長さを計算します。
     */
    float       Magnitude() const;
    
    /*!
        SqrMagnitude
        @unity-compatible   true
        ベクトルの長さの2乗を計算します。
     */
    float       SqrMagnitude() const;
    
    /*!
        normalized
        @unity-compatible   true
        大きさを1に正規化したベクトルを返します。
     */
    Vector3     Normalized() const;

    /*!
        Normalize
        @unity-compatible   true
        このベクトルの大きさを1に正規化します。
     */
    void        Normalize();

    /*!
        Project
        @unity-compatible   true
        ベクトル b の上にベクトル a を投影したベクトルを返します。
     */
    static Vector3  Project(const Vector3& a, const Vector3& b);

    /*!
        ProjectOnPlane
        @unity-compatible   true
        法線ベクトルによって定義される平面上にベクトルを射影します。
     */
    static Vector3  ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal);

    /*!
        Set
        @unity-compatible   true
        既存の Vector3 に x、y、z の成分を設定します。
     */
    void        Set(float x, float y, float z);

    /*!
        ToString
        @unity-compatible   true
        ベクトルの各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString() const override;

    /*!
        ToString
        @unity-compatible   true
        各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString(const std::string& format) const;

    /*!
        c_str
        ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str() const override;

    /*!
        c_str
        各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
     */
    const char* c_str(const std::string& format) const;

public:
    /*!
        @task   演算子のオーバーロード
     */
    
    /*!
        operator=
     */
    Vector3&  operator=(const Vector3& vec);
    
    
    /*!
        operator-
     */
    Vector3   operator-() const;
    
    /*!
        operator+
     */
    Vector3   operator+(const Vector3& vec) const;
    
    /*!
        operator-
     */
    Vector3   operator-(const Vector3& vec) const;
    
    /*!
        operator*
     */
    Vector3   operator*(const Vector3& vec) const;
    
    /*!
        operator/
     */
    Vector3   operator/(const Vector3& vec) const;
    
    /*!
        operator*
     */
    Vector3   operator*(float value) const;
    
    /*!
        operator/
     */
    Vector3   operator/(float value) const;
    
    friend Vector3 operator*(float value, const Vector3& vec);
    
    
    /*!
        operator+=
     */
    Vector3&  operator+=(const Vector3& vec);
    
    /*!
        operator-=
     */
    Vector3&  operator-=(const Vector3& vec);
    
    /*!
        operator*=
     */
    Vector3&  operator*=(const Vector3& vec);
    
    /*!
        operator/=
     */
    Vector3&  operator/=(const Vector3& vec);
    
    /*!
        operator*=
     */
    Vector3&  operator*=(float value);
    
    /*!
        operator/=
     */
    Vector3&  operator/=(float value);
    
    /*!
        operator==
     */
    bool        operator==(const Vector3& vec) const;
    
    /*!
        operator!=
     */
    bool        operator!=(const Vector3& vec) const;

    /*!
        operator[]
     */
    float&      operator[](int index);

    operator Vector2() const;

};


#endif  //#ifndef __VECTOR3_HPP__

