//
//  Vector2.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
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
#pragma mark - Static 定数
public:

    /// 要素が(0, -1)となるVector2の定数です。
    static const Vector2&    down;
    
    /// 要素が(-1, 0)となるVector2の定数です。
    static const Vector2&    left;
    
    /// 要素が(1, 1)となるVector2の定数です。
    static const Vector2&    one;

    /// 要素が(1, 0)となるVector2の定数です。
    static const Vector2&    right;

    /// 要素が(0, 1)となるVector2の定数です。
    static const Vector2&    up;

    /// 要素が(0, 0)となるVector2の定数です。
    static const Vector2&    zero;


#pragma mark - Static 関数
public:

    /// 2点間の角度を返します。
    static float    Angle(const Vector2& from, const Vector2& to);

    /// 大きさをmaxLengthにクランプしたベクトルを返します。
    static Vector2  ClampMagnitude(const Vector2& vector, float maxLength);
    
    /// 2つのベクトルのクロス積（外積）を返します。
    static float    Cross(const Vector2& lhs, const Vector2& rhs);

    /// 2つのベクトル間の距離を返します。
    static float    Distance(const Vector2& a, const Vector2& b);

    /// 2つのベクトルのドット積（内積）を返します。
    static float    Dot(const Vector2& lhs, const Vector2& rhs);
    
    /// 2つのベクトルのEase-In補完を計算します。
    static Vector2  EaseIn(const Vector2& a, const Vector2& b, float t);

    /// 2つのベクトルのEase-In-Out補完を計算します。
    static Vector2  EaseInOut(const Vector2& a, const Vector2& b, float t);

    /// 2つのベクトルのEase-Out補完を計算します。
    static Vector2  EaseOut(const Vector2& a, const Vector2& b, float t);
    
    /// ベクトルaとbの間でtの値による線形補間を計算します。
    /// パラメーターtは[0,1]の範囲で制限されます。
    static Vector2  Lerp(const Vector2& a, const Vector2& b, float t);

    /// ベクトルaとbの間でtの値による線形補間を計算します。
    /// パラメーターtの範囲は制限されません。
    static Vector2  LerpUnclamped(const Vector2& a, const Vector2& b, float t);

    /// 2つのベクトルの各成分の最大の要素からなるベクトルを返します。
    static Vector2  Max(const Vector2& a, const Vector2& b);
    
    /// 2つのベクトルの各成分の最小の要素からなるベクトルを返します。
    static Vector2  Min(const Vector2& a, const Vector2& b);

    /// 現在位置をターゲットの方向に移動させます。
    static Vector2  MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);
    
    /// 法線を使って反射させたベクトルを返します。
    static Vector2  Reflect(const Vector2& inDirection, const Vector2& inNormal);

    /// 2つのベクトルの各成分を乗算します。
    static Vector2   Scale(const Vector2& a, const Vector2& b);

    /// ベクトルを指定されたゴールに徐々に近づけていきます。
    static Vector2  SmoothDamp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

    /// 2つのベクトルのSmoothStep補完を計算します。
    static Vector2  SmoothStep(const Vector2& a, const Vector2& b, float t);


#pragma mark - Public 変数
public:
    /// ベクトルのx成分
    float x;

    /// ベクトルのy成分
    float y;


#pragma mark - コンストラクタ
public:

    /// コンストラクタ。すべての要素を0で初期化します。
    Vector2();
    
    /// コンストラクタ。x, yの要素を指定して初期化します。
    Vector2(float x, float y);
    
    /// コピーコンストラクタ
    Vector2(const Vector2& vec);

    
#pragma mark - Public 関数
public:

    /// ベクトルの長さを取得します。
    float       Magnitude() const;
    
    /// 大きさを1に正規化したベクトルを返します。
    Vector2     Normalized() const;
    
    /// このベクトルの大きさを1に正規化します。
    void        Normalize();

    /// ベクトルの長さの2乗を取得します。
    float       SqrMagnitude() const;
    
    /// このベクトルのx, yの成分を設定します。
    void        Set(float x, float y);

    /// ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString() const override;

    /// 各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString(const std::string& format) const;

    /// ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str() const override;

    /// 各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str(const std::string& format) const;


#pragma mark - 演算子のオーバーロード
public:

    /// このベクトルにベクトルvecの内容をコピーします。
    Vector2& operator=(const Vector2& vec);

    /// このベクトルの各要素に-1を掛けたベクトルを生成します。
    Vector2 operator-() const;
    
    /// このベクトルとベクトルvecの各要素を足し合わせたベクトルを生成します。
    Vector2 operator+(const Vector2& vec) const;
    
    /// このベクトルからベクトルvecの各要素を引いたベクトルを生成します。
    Vector2 operator-(const Vector2& vec) const;
    
    /// 2つのベクトルの各要素同士を掛け合わせたベクトルを生成します。
    Vector2 operator*(const Vector2& vec) const;
    
    /// このベクトルの各要素を、ベクトルvecの同じ要素で割ったベクトルを生成します。
    Vector2 operator/(const Vector2& vec) const;
    
    /// このベクトルの各要素にスカラ値valueを掛け合わせたベクトルを生成します。
    Vector2 operator*(float value) const;
    
    /// このベクトルの各要素をスカラ値valueで割ったベクトルを生成します。
    Vector2 operator/(float value) const;

    /// スカラ値とベクトルの掛け算を計算します。
    friend Vector2 operator*(float value, const Vector2& vec);

    /// このベクトルの各要素に、ベクトルvecの同じ要素の値を足し合わせます。
    Vector2&    operator+=(const Vector2& vec);
    
    /// このベクトルの各要素から、ベクトルvecの同じ要素の値を引きます。
    Vector2&    operator-=(const Vector2& vec);
    
    /// このベクトルの各要素に、ベクトルvecの同じ要素の値を掛け合わせます。
    Vector2&    operator*=(const Vector2& vec);
    
    /// このベクトルの各要素を、ベクトルvecの同じ要素の値で割ります。
    Vector2&    operator/=(const Vector2& vec);
    
    /// このベクトルの各要素にスカラ値valueを掛けます。
    Vector2&    operator*=(float value);
    
    /// このベクトルの各要素をスカラ値valueで割ります。
    Vector2&    operator/=(float value);
    
    /// 与えられたベクトルがこのベクトルと等しいかを判定します。
    bool        operator==(const Vector2& vec) const;
    
    /// 与えられたベクトルがこのベクトルと等しくないかを判定します。
    bool        operator!=(const Vector2& vec) const;
    
    /// [0]や[1]を使用して、x成分やy成分にアクセスします。
    float&      operator[](int index);

    /// このベクトルをVector3に変換します。z要素はゼロになります。
    operator Vector3() const;

};


#endif  //#ifndef __VECTOR2_HPP__


