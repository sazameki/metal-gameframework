//
//  Vector4.hpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
//

#ifndef __VECTOR4_HPP__
#define __VECTOR4_HPP__


#include "GMObject.hpp"

class Matrix4x4;
class Vector2;
class Vector3;
class Quaternion;


/// 4次元ベクトルを表す構造体です。
struct Vector4 : public GMObject
{
#pragma mark - Static 定数

    /// すべての要素が1の4次元ベクトル定数
    static const Vector4&    one;

    /// すべての要素が0の4次元ベクトル定数
    static const Vector4&    zero;
    

#pragma mark - Static 関数

    /// 2つのベクトル間の距離を返します。
    static float    Distance(const Vector2& a, const Vector2& b);

    /// 2つのベクトルのドット積（内積）を返します。
    static float    Dot(const Vector4& lhs, const Vector4& rhs);

    /// 2つのベクトルのEase-In補完を計算します。
    static Vector4  EaseIn(const Vector4& vec1, const Vector4& vec2, float amount);

    /// 2つのベクトルのEase-In-Out補完を計算します。
    static Vector4  EaseInOut(const Vector4& vec1, const Vector4& vec2, float amount);

    /// 2つのベクトルのEase-Out補完を計算します。
    static Vector4  EaseOut(const Vector4& vec1, const Vector4& vec2, float amount);

    /// ベクトルaとbの間でtの値による線形補間を計算します。
    /// パラメーターtは[0,1]の範囲で制限されます。
    static Vector4  Lerp(const Vector4& vec1, const Vector4& vec2, float amount);

    /// ベクトルaとbの間でtの値による線形補間を計算します。
    /// パラメーターtは制限されません。
    static Vector4  LerpUnclamped(const Vector4& vec1, const Vector4& vec2, float amount);

    /// 2つのベクトルの各成分の最大の要素からなるベクトルを返します。
    static Vector4  Max(const Vector4& vec1, const Vector4& vec2);

    /// 2つのベクトルの各成分の最小の要素からなるベクトルを返します。
    static Vector4  Min(const Vector4& vec1, const Vector4& vec2);

    /// 現在位置をターゲットの方向に移動させます。
    static Vector4 MoveTowards(const Vector4& current, const Vector4& target, float maxDistanceDelta);

    /// ベクトル b の上にベクトル a を投影したベクトルを返します。
    static Vector4  Project(const Vector4& a, const Vector4& b);

    /// 2つのベクトルの各成分を乗算します。
    static Vector4  Scale(const Vector4& a, const Vector4& b);

    /// 2つのベクトルのSmoothStep補完を計算します。
    static Vector4  SmoothStep(const Vector4& a, const Vector4& b, float t);


#pragma mark - Public 変数

    /// このベクトルのx成分
    float x;
    
    /// このベクトルのy成分
    float y;
    
    /// このベクトルのz成分
    float z;
    
    /// このベクトルのw成分
    float w;


#pragma mark - コンストラクタ

    /// コンストラクタ。すべての要素を0で初期化します。
    Vector4();
    
    /// コンストラクタ。x, y, z, wの要素の値を指定して初期化します。
    Vector4(float x, float y, float z, float w);
    
    /// コンストラクタ。Vector2のx,y成分にzとwの要素の値を合わせたVector4を作成します。
    Vector4(const Vector2& vec, float z, float w);
    
    /// コンストラクタ。Vector3のx,y,z成分にwの要素の値を合わせたVector4を作成します。
    Vector4(const Vector3& vec, float w);
    
    /// コピーコンストラクタ
    Vector4(const Vector4& vec);
    

#pragma mark - Public 関数

    /// ベクトルの長さを計算します。
    float       Magnitude() const;
    
    /// ベクトルの長さの2乗を計算します。
    float       SqrMagnitude() const;
    
    /// 大きさを1に正規化したベクトルを返します。
    Vector4     Normalized() const;
    
    /// このベクトルの大きさを1に正規化します。
    void        Normalize();
    
    /// このベクトルの x, y, z, w の成分を設定します。
    void        Set(float x, float y, float z, float w);

    /// ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString() const override;

    /// 各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString(const std::string& format) const;

    /// ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str() const override;

    /// 各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str(const std::string& format) const;


#pragma mark - 演算子のオーバーロード

    /*!
        operator=
     */
    Vector4&  operator=(const Vector4& vec);
    
    
    /*!
        operator-
     */
    Vector4   operator-() const;
    
    /*!
        operator+
     */
    Vector4   operator+(const Vector4& vec) const;
    
    /*!
        operator-
     */
    Vector4   operator-(const Vector4& vec) const;
    
    /*!
        operator*
     */
    Vector4   operator*(const Vector4& vec) const;
    
    /*!
        operator/
     */
    Vector4   operator/(const Vector4& vec) const;
    
    /*!
        operator*
     */
    Vector4   operator*(float value) const;
    
    /*!
        operator/
     */
    Vector4   operator/(float value) const;


    friend Vector4 operator*(float value, const Vector4& vec);

    
    /*!
        operator+=
     */
    Vector4&  operator+=(const Vector4& vec);
    
    /*!
        operator-=
     */
    Vector4&  operator-=(const Vector4& vec);
    
    /*!
        operator*=
     */
    Vector4&  operator*=(const Vector4& vec);
    
    /*!
        operator/=
     */
    Vector4&  operator/=(const Vector4& vec);
    
    /*!
        operator*=
     */
    Vector4&  operator*=(float value);
    
    /*!
        operator/=
     */
    Vector4&  operator/=(float value);
    
    
    /*!
        operator==
     */
    bool        operator==(const Vector4& vec) const;
    
    /*!
        operator!=
     */
    bool        operator!=(const Vector4& vec) const;

    /// [0]や[1]や[2]や[3]を使用して、x成分, y成分, z成分, w成分にアクセスします。
    float&      operator[](int index);

    /// このベクトルをVector2に変換します。z要素とw要素はドロップされます。
    operator Vector2() const;

    /// このベクトルをVector3に変換します。w要素はドロップされます。
    operator Vector3() const;

};


#endif  //#ifndef __VECTOR4_HPP__


