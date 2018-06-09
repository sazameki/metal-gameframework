//
//  Quaternion.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
//

#ifndef __QUATERNION_HPP__
#define __QUATERNION_HPP__


#include "GMObject.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"


struct Matrix4x4;


/// クォータニオンを表現するクラスです。
struct Quaternion : public GMObject
{    
#pragma mark - Static 変数

    /// 単位回転を表すクォータニオンです。
    static const Quaternion&    identity;


#pragma mark - Static 関数

    /// 2つの回転 a と b の間の角度をラジアン単位で返します。
    static float        Angle(const Quaternion& a, const Quaternion& b);

    /// axis の周りを degree 度回転する回転を作成します。
    static Quaternion   AngleAxis(float degree, const Vector3& axis);

    /// 2つの回転のドット積（内積）を返します。
    static float        Dot(const Quaternion& a, const Quaternion& b);

    /// オイラー角を元にクォータニオンを作成します。
    static Quaternion   Euler(float xDegree, float yDegree, float zDegree);

    /// オイラー角を元にクォータニオンを作成します。
    static Quaternion   Euler(const Vector3& euler);

    /// 2つのクォータニオンの間でEase-In補完を計算します。
    static Quaternion   EaseIn(const Quaternion& q1, const Quaternion& q2, float t);
    
    /// 2つのクォータニオンの間でEase-In-Out補完を計算します。
    static Quaternion   EaseInOut(const Quaternion& q1, const Quaternion& q2, float t);
    
    /// 2つのクォータニオンの間でEase-Out補完を計算します。
    static Quaternion   EaseOut(const Quaternion& q1, const Quaternion& q2, float t);

    /// fromDirのベクトルをtoDirのベクトルに回転させるクォータニオンを作成します。
    static Quaternion   FromToRotation(const Vector3& fromDir, const Vector3& toDir);

    /// クォータニオンの正反対の値となる値を返します。
    static Quaternion   Inverse(const Quaternion& rotation);

    /// 2つのクォータニオンの間で線形補完を計算します。
    /// パラメータtの値は、[0,1]の範囲に制限されます。
    static Quaternion   Lerp(const Quaternion& q1, const Quaternion& q2, float t);

    /// 2つのクォータニオンの間で線形補完を計算します。
    /// パラメータtの値は制限されません。
    static Quaternion   LerpUnclamped(const Quaternion& q1, const Quaternion& q2, float t);

    /// 方向ベクトルupwardsを軸として、forwardの方向を向くように回転させるクォータニオンを作成します。
    static Quaternion   LookRotation(const Vector3& forward, const Vector3& upwards = Vector3::up);

    /// fromの回転をtoの回転に変えるようなクォータニオンを作成します。
    static Quaternion   RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);

    /// 2つのクォータニオンの球面線形補間を計算します。
    /// パラメータtは[0,1]の範囲にクランプされます。
    static Quaternion   Slerp(const Quaternion& q1, const Quaternion& q2, float t);

    /// 2つのクォータニオンの球面線形補間を計算します。
    /// パラメータtの値は制限されません。
    static Quaternion   SlerpUnclamped(const Quaternion& q1, const Quaternion& q2, float t);

    /// 2つのクォータニオンの間でSmoothStep補完を計算します。
    static Quaternion   SmoothStep(const Quaternion& q1, const Quaternion& q2, float t);

    
#pragma mark - Public 変数

    /// クォータニオンのx成分
    float x;

    /// クォータニオンのy成分
    float y;

    /// クォータニオンのz成分
    float z;

    /// クォータニオンのz成分
    float w;
    

#pragma mark - コンストラクタ

    /// コンストラクタ。すべての要素の値を0で初期化します。
    Quaternion();

    /// コンストラクタ。すべての要素の値を指定して初期化します。
    Quaternion(float x, float y, float z, float w);
    
    /// コピーコンストラクタ
    Quaternion(const Quaternion& quat);
    
    /// コンストラクタ。Vector4のx,y,z,wの4つの値をそのままクォータニオンの要素の値としてコピーします。
    Quaternion(const Vector4& vec);

    /// コンストラクタ。Matrix4x4の回転成分だけを取り出してクォータニオンで表します。
    Quaternion(const Matrix4x4& mat);


#pragma mark - Public 関数

    /// このクォータニオンと与えられたクォータニオンを結合したクォータニオンを作成します。
    Quaternion      Concat(const Quaternion& quat) const;

    /// このクォータニオンの共役クォータニオンを計算します。
    Quaternion&     Conjugate();

    /// このクォータニオンの大きさを計算します。
    float           Magnitude() const;
    
    /// このクォータニオンを正規化したクォータニオンを生成します。
    Quaternion      Normalized() const;
    
    /// このクォータニオンを正規化します。
    void            Normalize();

    /// このクォータニオンの x, y, z, w の各成分の値を設定します。
    void            Set(float x, float y, float z, float w);

    /// このクォータニオンの大きさの2乗を計算します。
    float           SqrMagnitude() const;
    
    /// このクォータニオンと同じ回転を表すMatrix4x4構造体を生成します。
    Matrix4x4       ToMatrix4x4() const;

    /// ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string     ToString() const override;

    /// 各要素に対して適用される書式を指定して、クォータニオンの各要素を見やすくフォーマットした文字列を返します。
    std::string     ToString(const std::string& format) const;

    /// クォータニオンの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char*     c_str() const override;

    /// 各要素に対して適用される書式を指定して、クォータニオンの各要素を見やすくフォーマットしたC言語文字列を返します。
    const char*     c_str(const std::string& format) const;


#pragma mark - 演算子のオーバーロード

    /// このクォータニオンにクォータニオンquatの内容をコピーします。
    Quaternion&     operator=(const Quaternion& quat);
    
    /// このクォータニオンの各要素に-1を掛けたクォータニオンを作成します。
    Quaternion      operator-() const;
    
    /// このクォータニオンの各要素に、クォータニオンquatの各要素を足し合わせたクォータニオンを作成します。
    Quaternion      operator+(const Quaternion& quat) const;
    
    /// このクォータニオンの各要素から、クォータニオンquatの各要素を引いたクォータニオンを作成します。
    Quaternion      operator-(const Quaternion& quat) const;
    
    /// このクォータニオンにクォータニオンquatを掛け合わせたクォータニオンを作成します。
    Quaternion      operator*(const Quaternion& quat) const;
    
    /// このクォータニオンの各要素に、スカラ値scaleを掛けたクォータニオンを作成します。
    Quaternion      operator*(float scale) const;

    /// Vector2にこのクォータニオンの回転を適用したVector2を計算します。
    Vector2         operator*(const Vector2& vec) const;

    /// Vector3にこのクォータニオンの回転を適用したVector3を計算します。
    Vector3         operator*(const Vector3& vec) const;

    /// Vector4にこのクォータニオンの回転を適用したVector4を計算します。
    Vector4         operator*(const Vector4& vec) const;

    /*!
        operator/
     */
    Quaternion      operator/(const Quaternion& quat) const;
    
    /*!
        operator/
     */
    Quaternion      operator/(float value) const;

    /*!
        operator+=
     */
    Quaternion&     operator+=(const Quaternion& quat);
    
    /*!
        operator-=
     */
    Quaternion&     operator-=(const Quaternion& quat);
    
    /// このクォータニオンに、クォータニオンquatを掛けます。
    Quaternion&     operator*=(const Quaternion& quat);
    
    /// このクォータニオンの各要素に、スカラ値valueを掛けます。
    Quaternion&     operator*=(float scale);
    
    /// このクォータニオンを、クォータニオンquatで割ります。
    Quaternion&     operator/=(const Quaternion& quat);

    /// このクォータニオンの各要素を、スカラ値valueで割ります。
    Quaternion&     operator/=(float value);

    /// 与えられたクォータニオンがこのクォータニオンと等しいかを判定します。
    bool        operator==(const Quaternion& quat) const;
    
    /// 与えられたクォータニオンがこのクォータニオンと等しくないかを判定します。
    bool        operator!=(const Quaternion& quat) const;

    /// クォータニオンの各要素の値をそのままコピーしたVector4構造体を作成します。
    operator   Vector4() const;

};


#endif  //#ifndef __QUATERNION_HPP__


