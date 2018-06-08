//
//  Mathf.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#ifndef __MATHF_HPP__
#define __MATHF_HPP__


#include "GMObject.hpp"


/*!
    一般的な数学関数をまとめて扱うためのクラスです。
 */
struct Mathf : public GMObject
{
    /// 度からラジアンに変換するための定数です。
    static const float  Deg2Rad;

    /// ごくわずかな浮動小数点の定数です。
    ///（Unityとの互換性のために用意していますが、C言語/C++では FLT_EPSILON (#include &lt;cfloat&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("FLT_EPSILON (#include <cfloat>) is recommended to use instead of Mathf::Epsilon.")))
    static const float  Epsilon;

    /// 無限大を表現する定数です。
    ///（Unityとの互換性のために用意していますが、C言語/C++では INFINITY (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("INFINITY (#include <cmath>) is recommended to use instead of Mathf::Infinity.")))
    static const float  Infinity;

    /// 負の無限大を表現する定数です。（Unityとの互換性のために用意していますが、C言語/C++では -INFINITY (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("-INFINITY (#include <cmath>) is recommended to use instead of Mathf::NegativeInfinity.")))
    static const float  NegativeInfinity;
    
    /// 円周率を表す定数です。（Unityとの互換性のために用意していますが、C言語/C++では M_PI (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("M_PI (#include <cmath>) is recommended to use instead of Mathf::PI.")))
    static const float  PI;

    /// ラジアンから度に変換するための定数です。
    static const float  Rad2Deg;

    
#pragma mark - Static 関数

    /// fの絶対値を返します。（Unityとの互換性のために用意していますが、C言語/C++では fabsf() (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("fabsf() (#include <cmath>) is recommended to use instead of Mathf::Abs().")))
    static float    Abs(float f);

    /// fのアークコサインを返します。（Unityとの互換性のために用意していますが、C言語/C++では acosf() (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("acosf() (#include <cmath>) is recommended to use instead of Mathf::Acos().")))
    static float    Acos(float f);

    /// 2つのfloat型の値がほぼ等しいかどうかを比較して判定します。
    static bool     Approximately(float a, float b);

    /// fのアークサインを返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では asinf() (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("asinf() (#include <cmath>) is recommended to use instead of Mathf::Asin().")))
    static float    Asin(float f);

    /// fのアークタンジェントを返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では atanf() (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("atanf() (#include <cmath>) is recommended to use instead of Mathf::Atan().")))
    static float    Atan(float f);

    /// タンジェントがy/xになる角度をラジアンで返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では atan2f() (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("atan2f() (#include <cmath>) is recommended to use instead of Mathf::Atan2().")))
    static float    Atan2(float y, float x);

    /// f以上の最小の整数を返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では ceilf() (#include &lt;cmath&gt;) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("ceilf() (#include <cmath>) is recommended to use instead of Mathf::Ceil().")))
    static float    Ceil(float f);

    /// f以上の最小の整数をint型で返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では ceilf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("ceilf() (#include <cmath>) is recommended to use instead of Mathf::Ceil().")))
    static int      CeilToInt(float f);

    /// min〜maxの範囲に値を制限します。
    static float    Clamp(float value, float min, float max);
    
    /// 0.0f〜1.0fの範囲に値を制限します。
    static float    Clamp01(float value);
    
    /// もっとも近い2のべき乗の値を返します。
    static int      ClosestPowerOfTwo(int value);

    /// ラジアンで表された角度に対するコサインを返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では cosf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("cosf() (#include <cmath>) is recommended to use instead of Mathf::Cos().")))
    static float    Cos(float rad);

    /// 度の単位で与えられた2つの角度に対して、その間の最小の角度の差を計算します。
    static float    DeltaAngle(float current, float target);

    /// [a, b]の範囲内で線形パラメータtにおけるEase-In補完を計算します。
    static float    EaseIn(float a, float b, float t);
    
    /// [a, b]の範囲内で線形パラメータtにおけるEase-In-Out補完を計算します。
    static float    EaseInOut(float a, float b, float t);

    /// [a, b]の範囲内で線形パラメータtにおけるEase-Out補完を計算します。
    static float    EaseOut(float a, float b, float t);

    /// ネイピア数eをx乗した数を計算します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では expf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("expf() (#include <cmath>) is recommended to use instead of Mathf::Exp().")))
    static float    Exp(float x);

    /// f以下の最大の整数を返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では floorf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("floorf() (#include <cmath>) is recommended to use instead of Mathf::Floor().")))
    static float    Floor(float f);

    /// f以下の最大の整数をint型で返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では floorf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("floorf() (#include <cmath>) is recommended to use instead of Mathf::FloorToInt().")))
    static int      FloorToInt(float f);

    /// [a, b]の範囲内で補間された値valueを生成するような線形パラメータtを計算します。
    static float    InverseLerp(float a, float b, float value);

    /// 値が2の乗数かどうかを判定します。
    static bool     IsPowerOfTwo(int value);

    /// aとbの間でパラメータtによる線形補間を計算します。パラメータtは[0, 1]の範囲に制限されます。
    static float    Lerp(float a, float b, float t);

    /// 単位が度で表される角度aとb 間でパラメータtによる線形補間を計算します。パラメータtは[0, 1]の範囲に制限されます。
    static float    LerpAngle(float a, float b, float t);

    /// a と b の間で t による線形補間を計算します。パラメーター t の範囲は制限されません。
    static float    LerpUnclamped(float a, float b, float t);
    
    /// 自然対数の底eに対する数xの対数を計算します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では std::logf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("logf() (#include <cmath>) is recommended to use instead of Mathf::Log().")))
    static float    Log(float x);
    
    /// 指定した底pに対する数fの対数を計算します。
    static float    Log(float f, float p);

    /// 常用対数の底10に対する数xの対数を計算します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では std::log10f() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("log10f() (#include <cmath>) is recommended to use instead of Mathf::Log10().")))
    static float    Log10(float x);

    /// 2つの値の最大値を返します。
    ///（Unityとの互換性のために用意していますが、C言語/C++では std::max() (#include <algorithm>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("std::max (#include <algorithm>) is recommended to use instead of Mathf::Max().")))
    static float    Max(float a, float b);

    /// 2つの値の最小値を返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では std::min() (#include <algorithm>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("std::min (#include <algorithm>) is recommended to use instead of Mathf::Min().")))
    static float    Min(float a, float b);
    
    /// Lerp()と同様に線形補間を行いますが、速度がmaxDeltaを超えないように調整されます。
    /// maxDeltaの値が負の場合はtargetから遠ざかります。
    static float    MoveTowards(float current, float target, float maxDelta);

    /// LerpAngle()と同様に線形補間を行いますが、速度がmaxDeltaを超えないように調整されます。
    /// 最適化のためにmaxDeltaの負の値はサポートされていません。そのため振動を引き起こす可能性があります。
    /// ターゲットからcurrentを遠ざけるためには、その角度に180を加えます。
    static float    MoveTowardsAngle(float current, float target, float maxDelta);

    /// 指定された数以上の2のべき乗の値を返します。
    static int      NextPowerOfTwo(int value);

    /// 0以上length以下の値となるように、値tを行き来させます。
    static float    PingPong(float t, float length);
    
    /// fのp乗を計算します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では std::powf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("powf() (#include <cmath>) is recommended to use instead of Mathf::Pow().")))
    static float    Pow(float f, float p);

    /// 0以上length以下の値となるように、値tをループさせます。
    static float    Repeat(float t, float length);

    /// fに最も近い整数を返します（四捨五入）。
    /// （Unityとの互換性のために用意していますが、C言語/C++では roundf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("roundf() (#include <cmath>) is recommended to use instead of Mathf::Round().")))
    static float    Round(float f);

    /// fに最も近い整数をint型で返します（四捨五入）。
    ///（Unityとの互換性のために用意していますが、C言語/C++では roundf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("roundf() (#include <cmath>) is recommended to use instead of Mathf::RoundToInt().")))
    static int      RoundToInt(float f);

    /// fがゼロ以上の数であれば1を、そうでなければ-1をリターンします。
    static float    Sign(float f);

    /// ラジアンで表された角度に対するサインを返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では sinf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("sinf() (#include <cmath>) is recommended to use instead of Mathf::Sin().")))
    static float    Sin(float rad);

    /// 徐々に時間をかけて望む目標に向かって値を変更します。
    /// 値はバネとダンパーのような関数によって滑らかに計算されます。
    static float    SmoothDamp(float current, float target, float& outCurrentVelocity, float smoothTime, float maxSpeed, float deltaTime);

    /// 度単位の角度を徐々に時間をかけて望む目標となる角度に向かって変更します。
    /// 値はバネとダンパーのような関数によって滑らかに計算されます。
    static float    SmoothDampAngle(float current, float target, float& outCurrentVelocity, float smoothTime, float maxSpeed, float deltaTime);

    /// fromからtoの値を、開始時には徐々に加速し、終了時には徐々に減速していくやり方で補間します。tは0.0f〜1.0fの範囲にクランプされます。
    static float    SmoothStep(float from, float to, float t);

    /// fの平方根を計算します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では sqrtf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("sqrtf() (#include <cmath>) is recommended to use instead of Mathf::Sqrt().")))
    static float    Sqrt(float f);
    
    /// ラジアンで表された角度に対するタンジェントを返します。
    /// （Unityとの互換性のために用意していますが、C言語/C++では tanf() (#include <cmath>) を使うのが一般的なので、使用は推奨されません。）
    __attribute__((deprecated("tanf() (#include <cmath>) is recommended to use instead of Mathf::Tan().")))
    static float    Tan(float rad);

};


#endif  //#ifndef __MATHF_HPP__


