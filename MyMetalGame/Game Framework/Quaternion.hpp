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
    static Quaternion   EaseIn(const Quaternion& a, const Quaternion& b, float t);
    
    /// 2つのクォータニオンの間でEase-In-Out補完を計算します。
    static Quaternion   EaseInOut(const Quaternion& a, const Quaternion& b, float t);
    
    /// 2つのクォータニオンの間でEase-Out補完を計算します。
    static Quaternion   EaseOut(const Quaternion& a, const Quaternion& b, float t);

    /*!
        FromToRotation
        @unity-compatible   true
     */
    static Quaternion   FromToRotation(const Vector3& fromDir, const Vector3& toDir);

    /// クォータニオンの正反対の値となる値を返します。
    static Quaternion   Inverse(const Quaternion& rotation);

    /// 2つのクォータニオンの間で線形補完を計算します。
    /// パラメーターtの値は、[0,1]の範囲に制限されます。
    static Quaternion   Lerp(const Quaternion& a, const Quaternion& b, float t);

    /// 2つのクォータニオンの間で線形補完を計算します。
    /// パラメーターtの値は制限されません。
    static Quaternion   LerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

    /*!
        LookRotation
        @unity-compatible   true (unsupported)
     */
    static Quaternion   LookRotation(const Vector3& forward, const Vector3& upwards = Vector3::up);

    /*!
        RotateTowards
        @unity-compatible   true
     */
    static Quaternion   RotateTowards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta);

    /*!
        Slerp
        @unity-compatible   true
     */
    static Quaternion   Slerp(const Quaternion& a, const Quaternion& b, float t);

    /*!
        SlerpUnclamped
        @unity-compatible   true
     */
    static Quaternion   SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

    /// 2つのクォータニオンの間でSmoothStep補完を計算します。
    static Quaternion   SmoothStep(const Quaternion& a, const Quaternion& b, float t);

    
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

    /*!
        Concat
        @unity-compatible   false
     */
    Quaternion      Concat(const Quaternion& quat) const;

    /*!
        Conjugate
        @unity-compatible   false
     */
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

    /*!
        operator=
     */
    Quaternion&     operator=(const Quaternion& quat);    
    
    /*!
        operator-
     */
    Quaternion      operator-() const;
    
    /*!
        operator+
     */
    Quaternion      operator+(const Quaternion& quat) const;
    
    /*!
        operator-
     */
    Quaternion      operator-(const Quaternion& quat) const;
    
    /*!
        operator*
     */
    Quaternion      operator*(const Quaternion& quat) const;
    
    /*!
        operator*
     */
    Quaternion      operator*(float scale) const;

    /*!
        operator*
     */
    Vector2         operator*(const Vector2& vec) const;

    /*!
        operator*
     */
    Vector3         operator*(const Vector3& vec) const;

    /*!
        operator*
     */
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
    
    /*!
        operator*=
     */
    Quaternion&     operator*=(const Quaternion& quat);
    
    /*!
        operator=
     */
    Quaternion&     operator*=(float scale);
    
    /*!
        operator/=
     */
    Quaternion&     operator/=(const Quaternion& quat);
    
    /*!
        operator/=
     */
    Quaternion&     operator/=(float value);

    /*!
        operator==
     */
    bool        operator==(const Quaternion& quat) const;
    
    /*!
        operator!=
     */
    bool        operator!=(const Quaternion& quat) const;

    /// クォータニオンの各要素の値をそのままコピーしたVector4構造体を作成します。
    operator   Vector4() const;

};


#endif  //#ifndef __QUATERNION_HPP__


