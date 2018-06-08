//
//  Vector2.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __VECTOR2_HPP__
#define __VECTOR2_HPP__


#include "GMObject.hpp"
#include <string>

struct Matrix4x4;
struct Quaternion;
struct Vector3;

    
/// 2次元ベクトルを表す構造体です。
struct Vector2 : public GMObject
{    
public:
    /*!
        @const  down
        @unity-compatible   true
        要素が(0, -1)となるVector2の定数です。
     */
    static const Vector2&    down;
    
    /*!
        @const  left
        @unity-compatible   true
        要素が(-1, 0)となるVector2の定数です。
     */
    static const Vector2&    left;
    
    /*!
        @const  one
        @unity-compatible   true
        要素が(1, 1)となるVector2の定数です。
     */
    static const Vector2&    one;

    /*!
        @const  right
        @unity-compatible   true
        要素が(1, 0)となるVector2の定数です。
     */
    static const Vector2&    right;

    /*!
        @const  up
        @unity-compatible   true
        要素が(0, 1)となるVector2の定数です。
     */
    static const Vector2&    up;

    /*!
        @const  zero
        @unity-compatible   true
        要素が(0, 0)となるVector2の定数です。
     */
    static const Vector2&    zero;

public:
    /*!
        @var    x
        ベクトルのx成分
     */
    float x;

    /*!
        @var    y
        ベクトルのy成分
     */
    float y;
    
    /*!
        @task   Static 関数
     */

    /*!
        Angle
        @unity-compatible   true
        2点間の角度を返します。
     */
    static float    Angle(const Vector2& from, const Vector2& to);

    /*!
        ClampMagnitude
        @unity-compatible   true
        大きさをmaxLengthにクランプしたベクトルを返します。
     */
    static Vector2  ClampMagnitude(const Vector2& vector, float maxLength);
    
    /*!
        Cross
        2つのベクトルの外積を返します。
     */
    static float    Cross(const Vector2& lhs, const Vector2& rhs);

    /*!
        Distance
        @unity-compatible   true
        2つのベクトル間の距離を返します。
     */
    static float    Distance(const Vector2& a, const Vector2& b);

    /*!
        Dot
        @unity-compatible   true
        2つのベクトルの内積を返します。
     */
    static float    Dot(const Vector2& lhs, const Vector2& rhs);
    
    /*!
        EaseIn
     */
    static Vector2  EaseIn(const Vector2& a, const Vector2& b, float t);

    /*!
        EaseInOut
     */
    static Vector2  EaseInOut(const Vector2& a, const Vector2& b, float t);

    /*!
        EaseOut
     */
    static Vector2  EaseOut(const Vector2& a, const Vector2& b, float t);
    
    /*!
        Lerp
        @unity-compatible   true
        ベクトル a と b の間で t の値による線形補間を計算します。
        パラメーター t は [0, 1] の範囲で制限されます。
     */
    static Vector2  Lerp(const Vector2& a, const Vector2& b, float t);

    /*!
        LerpUnclamped
        @unity-compatible   true
        ベクトル a と b の間で t の値による線形補間を計算します。
        パラメーター t の範囲は制限されません。
     */
    static Vector2  LerpUnclamped(const Vector2& a, const Vector2& b, float t);

    /*!
        Max
        @unity-compatible   true
        2つのベクトルの各成分の最大の要素からなるベクトルを返します。
     */
    static Vector2  Max(const Vector2& a, const Vector2& b);
    
    /*!
        Min
        @unity-compatible   true
        2つのベクトルの各成分の最小の要素からなるベクトルを返します。
     */
    static Vector2  Min(const Vector2& a, const Vector2& b);
    
    /*!
        MoveTowards
        現在位置をターゲットの方向に移動させます。
     */
    static Vector2  MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
    
    /*!
        Reflect
        法線を使って反射させたベクトルを返します。
     */
    static Vector2  Reflect(const Vector2& inDirection, const Vector2& inNormal);

    /*!
        Scale
        @unity-compatible   true
        2つのベクトルの各成分を乗算します。
     */
    static Vector2   Scale(const Vector2& a, const Vector2& b);

    /*!
        SmoothDamp
        @unity-compatible   true
        ベクトルを指定されたゴールに徐々に近づけていきます。
     */
    static Vector2  SmoothDamp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
    
    static Vector2  SmoothStep(const Vector2& a, const Vector2& b, float t);


    /*!
        @task   コンストラクタ
     */
    
    /*!
        Vector2
        @unity-compatible   false
     */
    Vector2();
    
    /*!
        Vector2
        @unity-compatible   true
     */
    Vector2(float x, float y);
    
    /*!
        Vector2
        @unity-compatible   false
     */
    Vector2(const Vector2& vec);

    
    /*!
        Public 関数
     */
    
    /*!
        Magnitude
        @unity-compatible   true
        ベクトルの長さを取得します。
     */
    float       Magnitude() const;
    
    /*!
        normalized
        @unity-compatible   true
        大きさを1に正規化したベクトルを返します。
     */
    Vector2     Normalized() const;
    
    /*!
        Normalize
        @unity-compatible   true
        このベクトルの大きさを1に正規化します。
     */
    void        Normalize();

    /*!
        SqrMagnitude
        @unity-compatible   true
        ベクトルの長さの2乗を取得します。
     */
    float       SqrMagnitude() const;
    
    /*!
        Set
        @unity-compatible   true
        既存の Vector2 に x、y の成分を設定します。
     */
    void        Set(float x, float y);

    /*!
        ToString
        ベクトルの各要素を見やすくフォーマットした文字列を返します。
     */
    std::string ToString() const override;

    /*!
        ToString
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
    Vector2& operator=(const Vector2& vec);
        
    /*!
        operator-
     */
    Vector2 operator-() const;
    
    /*!
        operator+
     */
    Vector2 operator+(const Vector2& vec) const;
    
    /*!
        operator-
     */
    Vector2 operator-(const Vector2& vec) const;
    
    /*!
        operator*
     */
    Vector2 operator*(const Vector2& vec) const;
    
    /*!
        operator/
     */
    Vector2 operator/(const Vector2& vec) const;
    
    /*!
        operator*
     */
    Vector2 operator*(float value) const;
    
    /*!
        operator/
     */
    Vector2 operator/(float value) const;
    
    friend Vector2 operator*(float value, const Vector2& vec);
    
    
    /*!
        operator+=
     */
    Vector2& operator+=(const Vector2& vec);
    
    /*!
        operator-=
     */
    Vector2& operator-=(const Vector2& vec);
    
    /*!
        operator*=
     */
    Vector2& operator*=(const Vector2& vec);
    
    /*!
        operator/=
     */
    Vector2& operator/=(const Vector2& vec);
    
    /*!
        operator*=
     */
    Vector2& operator*=(float value);
    
    /*!
        operator/=
     */
    Vector2& operator/=(float value);
    
    /*!
        operator==
     */
    bool        operator==(const Vector2& vec) const;
    
    /*!
        operator!=
     */
    bool        operator!=(const Vector2& vec) const;
    
    /// [0]や[1]を使用して、x成分やy成分にアクセスします。
    float&      operator[](int index);

    /// Vector3に変換します。z要素はゼロになります。
    operator Vector3() const;

};


#endif  //#ifndef __VECTOR2_HPP__


