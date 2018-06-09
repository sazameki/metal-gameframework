//
//  Vector3.hpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
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
#pragma mark - Static 定数

    /// 要素が(0, 0, -1)となるVector3の定数です。
    static const Vector3&    back;

    /// 要素が(0, -1, 0)となるVector3の定数です。
    static const Vector3&    down;
    
    /// 要素が(0, 0, 1)となるVector3の定数です。
    static const Vector3&    forward;
    
    /// 要素が(-1, 0, 0)となるVector3の定数です。
    static const Vector3&    left;
    
    /// すべての要素が1のVector3の定数です。
    static const Vector3&    one;
    
    /// 要素が(1, 0, 0)となるVector3の定数です。
    static const Vector3&    right;
    
    /// 要素が(0, 1, 0)となるVector3の定数です。
    static const Vector3&    up;
    
    /// すべての要素が0のVector3の定数です。
    static const Vector3&    zero;


#pragma mark - Static 関数

    /// from と to の2点間の角度を返します。
    static float    Angle(const Vector3& from, const Vector3& to);

    /// 大きさを maxLength までに制限した vector のコピーを返します。
    static Vector3  ClampMagnitude(const Vector3& vector, float maxLength);

    /// 2つのベクトルの外積を計算します。
    static Vector3  Cross(const Vector3 &lhs, const Vector3 &rhs);

    /// 2つのベクトル間の距離を返します。
    static float    Distance(const Vector3& a, const Vector3& b);

    /// 2つのベクトルのドット積（内積）を返します。
    static float    Dot(const Vector3& lhs, const Vector3& rhs);

    /// 2つのベクトルのEase-In補完を計算します。
    static Vector3  EaseIn(const Vector3& a, const Vector3& b, float t);

    /// 2つのベクトルのEase-In-Out補完を計算します。
    static Vector3  EaseInOut(const Vector3& a, const Vector3& b, float t);

    /// 2つのベクトルのEase-Out補完を計算します。
    static Vector3  EaseOut(const Vector3& a, const Vector3& b, float t);

    /// ベクトルaとbの間でtの値による線形補間を計算します。
    /// パラメーターtは[0,1]の範囲で制限されます。
    static Vector3  Lerp(const Vector3& a, const Vector3& b, float t);

    /// ベクトルaとbの間でtの値による線形補間を計算します。
    /// パラメーターtの範囲は制限されません。
    static Vector3  LerpUnclamped(const Vector3& a, const Vector3& b, float t);

    /// 2つのベクトルの各成分の最大の要素からなるベクトルを返します。
    static Vector3  Max(const Vector3& a, const Vector3& b);

    /// 2つのベクトルの各成分の最小の要素からなるベクトルを返します。
    static Vector3  Min(const Vector3& a, const Vector3& b);

    /// 現在位置をターゲットの方向に移動させます。
    static Vector3  MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);

    // Unity互換の関数だが、実装していない。
    //static void     OrthoNormalize(Vector3& normal, Vector3& tangent);

    // Unity互換の関数だが、実装していない。
    //static void     OrthoNormalize(Vector3& normal, Vector3& tangent, Vector3& binormal);

    /// 法線で定義された平面でベクトルを反射します。
    static Vector3  Reflect(const Vector3 &inDirection, const Vector3 &inNormal);

    // Unity互換の関数だが、実装していない。
    //static Vector3  RotateTowards(const Vector3& current, const Vector3& target, float maxRadiansDelta, float maxMagnitudeDelta);

    /// 2つのベクトルの各成分を乗算します。
    static Vector3  Scale(const Vector3& a, const Vector3& b);

    /// 2つのベクトルの球面線形補間を計算します。
    /// パラメーターtは[0,1]の範囲にクランプされます。
    static Vector3  Slerp(const Vector3& a, const Vector3& b, float t);

    /// 2つのベクトルの球面線形補間を計算します。
    /// パラメーターtの値は制限されません。
    static Vector3  SlerpUnclamped(const Vector3& a, const Vector3& b, float t);

    /// ベクトルを指定されたゴールに徐々に近づけていきます。
    static Vector3  SmoothDamp(const Vector3 &current, const Vector3 &target, Vector3 &currentVelocity,
                               float smoothTime, float maxSpeed, float deltaTime);

    /// 2つのベクトルのSmoothStep補完を計算します。
    static Vector3 SmoothStep(const Vector3& a, const Vector3& b, float t);

    
#pragma mark - Public 変数

    /// ベクトルのx成分
    float x;
    
    /// ベクトルのy成分
    float y;
    
    /// ベクトルのz成分
    float z;


#pragma mark - コンストラクタ

    /// コンストラクタ。すべての要素を0で初期化します。
    Vector3();

    /// コンストラクタ。x, y, zの要素を指定して初期化します。
    Vector3(float x, float y, float z);
    

    /// コンストラクタ。Vector2のx,y成分にzの要素の値を合わせたVector3を作成します。
    Vector3(const Vector2& vec, float z);
    
    /// コピーコンストラクタ
    Vector3(const Vector3& vec);

    
#pragma mark - Public 関数

    /// ベクトルの長さを計算します。
    float       Magnitude() const;
    
    /// ベクトルの長さの2乗を計算します。
    float       SqrMagnitude() const;
    
    /// 大きさを1に正規化したベクトルを返します。
    Vector3     Normalized() const;

    /// このベクトルの大きさを1に正規化します。
    void        Normalize();

    /// ベクトル b の上にベクトル a を投影したベクトルを返します。
    static Vector3  Project(const Vector3& a, const Vector3& b);

    /// 法線ベクトルによって定義される平面上にベクトルを射影します。
    static Vector3  ProjectOnPlane(const Vector3& vector, const Vector3& planeNormal);

    /// このベクトルの x, y, z の成分を設定します。
    void        Set(float x, float y, float z);

    /// ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString() const override;

    /// 各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString(const std::string& format) const;

    /// ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str() const override;

    /// 各要素に対して適用される書式を指定して、ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str(const std::string& format) const;


#pragma mark - 演算子のオーバーロード

    /// このベクトルにベクトルvecの内容をコピーします。
    Vector3&  operator=(const Vector3& vec);
    
    /// このベクトルの各要素に-1を掛けたベクトルを生成します。
    Vector3   operator-() const;
    
    /// このベクトルとベクトルvecの各要素を足し合わせたベクトルを生成します。
    Vector3   operator+(const Vector3& vec) const;
    
    /// このベクトルからベクトルvecの各要素を引いたベクトルを生成します。
    Vector3   operator-(const Vector3& vec) const;
    
    /// 2つのベクトルの各要素同士を掛け合わせたベクトルを生成します。
    Vector3   operator*(const Vector3& vec) const;
    
    /// このベクトルの各要素を、ベクトルvecの同じ要素で割ったベクトルを生成します。
    Vector3   operator/(const Vector3& vec) const;
    
    /// このベクトルの各要素にスカラ値valueを掛け合わせたベクトルを生成します。
    Vector3   operator*(float value) const;
    
    /// このベクトルの各要素をスカラ値valueで割ったベクトルを生成します。
    Vector3   operator/(float value) const;
    
    /// スカラ値とベクトルの掛け算を計算します。
    friend Vector3 operator*(float value, const Vector3& vec);
    
    /// このベクトルの各要素に、ベクトルvecの同じ要素の値を足し合わせます。
    Vector3&  operator+=(const Vector3& vec);
    
    /// このベクトルの各要素から、ベクトルvecの同じ要素の値を引きます。
    Vector3&  operator-=(const Vector3& vec);
    
    /// このベクトルの各要素に、ベクトルvecの同じ要素の値を掛け合わせます。
    Vector3&  operator*=(const Vector3& vec);
    
    /// このベクトルの各要素を、ベクトルvecの同じ要素の値で割ります。
    Vector3&  operator/=(const Vector3& vec);
    
    /// このベクトルの各要素にスカラ値valueを掛けます。
    Vector3&  operator*=(float value);
    
    /// このベクトルの各要素をスカラ値valueで割ります。
    Vector3&  operator/=(float value);
    
    /// 与えられたベクトルがこのベクトルと等しいかを判定します。
    bool        operator==(const Vector3& vec) const;
    
    /// 与えられたベクトルがこのベクトルと等しくないかを判定します。
    bool        operator!=(const Vector3& vec) const;

    /// [0]や[1]や[2]を使用して、x成分, y成分, z成分にアクセスします。
    float&      operator[](int index);

    /// このベクトルをVector2に変換します。z要素はドロップされます。
    operator Vector2() const;

};


#endif  //#ifndef __VECTOR3_HPP__

