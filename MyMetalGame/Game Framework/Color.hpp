//
//  Color.hpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2018 Satoshi Numata. All rights reserved.
//

#ifndef __COLOR_HPP__
#define __COLOR_HPP__

#include "GMObject.hpp"


struct Vector3;
struct Vector4;

/// ゲームで使用される色を表現するためのクラスです。
struct Color : public GMObject
{
#pragma mark - Static 変数

    /// RGBAが(0, 0, 0, 1)の黒を表す色の定数です。
    static const Color&     black;

    /// RGBAが(0, 0, 1, 1)の青を表す色の定数です。
    static const Color&     blue;

    /// RGBAが(0, 0, 0, 0)の透明色を表す色の定数です。
    static const Color&     clear;

    /// RGBAが(0, 1, 1, 1)のシアンを表す色の定数です。
    static const Color&     cyan;

    /// RGBAが(0, 0, 0.7, 1)の暗い青を表す色の定数です。
    static const Color&     darkblue;

    /// RGBAが(0, 0.5, 0.5, 1)の暗いシアンを表す色の定数です。
    static const Color&     darkcyan;

    /// RGBAが(0.25, 0.25, 0.25, 1)の暗いグレーを表す色の定数です。
    static const Color&     darkgray;

    /// RGBAが(0, 0, 0.5, 1)の暗い青を表す色の定数です。
    static const Color&     darkgreen;

    /// RGBAが(0.5, 0.25, 0, 1)の暗いオレンジを表す色の定数です。
    static const Color&     darkorange;

    /// RGBAが(0.6, 0.08, 0.3, 1)の暗いピンクを表す色の定数です。
    static const Color&     darkpink;

    /// RGBAが(0.5, 0, 0.5, 1)の暗い紫を表す色の定数です。
    static const Color&     darkpurple;

    /// RGBAが(0.6, 0, 0, 1.0)の暗い赤を表す色の定数です。
    static const Color&     darkred;

    /// RGBAが(0.5, 0.5, 0, 1)の暗い黄色を表す色の定数です。
    static const Color&     darkyellow;

    /// RGBAが(0.5, 0.5, 0.5, 1)のグレーを表す色の定数です。
 	static const Color&     gray;

    /// RGBAが(0, 1, 0, 1)の緑を表す色の定数です。
 	static const Color&     green;

    /// RGBAが(0.5, 0.5, 1, 1)の明るい青を表す色の定数です。
    static const Color&     lightblue;

    /// RGBAが(0.65, 1, 1, 1)の明るいシアンを表す色の定数です。
    static const Color&     lightcyan;

    /// RGBAが(0.75, 0.75, 0.75, 1)の明るいグレーを表す色の定数です。
    static const Color&     lightgray;

    /// RGBAが(0.5, 1, 0.5, 1)の明るい緑を表す色の定数です。
    static const Color&     lightgreen;

    /// RGBAが(1, 0.75, 0.5, 1)の明るいオレンジを表す色の定数です。
    static const Color&     lightorange;

    /// RGBAが(1, 0.5, 0.8, 1)の明るいピンクを表す色の定数です。
    static const Color&     lightpink;

    /// RGBAが(1, 0.5, 1, 1)の明るい紫を表す色の定数です。
    static const Color&     lightpurple;

    /// RGBAが(1, 0.5, 0.5, 1)の明るい赤を表す色の定数です。
    static const Color&     lightred;

    /// RGBAが(1, 1, 0.65, 1)の明るい黄色を表す色の定数です。
    static const Color&     lightyellow;

    /// RGBAが(1, 0.5, 0, 1)のオレンジを表す色の定数です。
    static const Color&     orange;

    /// RGBAが(1, 0.25, 0.6, 1)のピンクを表す色の定数です。
    static const Color&     pink;

    /// RGBAが(1, 0, 1, 1)の紫を表す色の定数です。
    static const Color&     purple;

    /// RGBAが(1, 0, 0, 1)の赤を表す色の定数です。
    static const Color&     red;

    /// RGBAが(1, 1, 1, 1)の白を表す色の定数です。
    static const Color&     white;

    /// RGBAが(1, 1, 0, 1)の黄色を表す色の定数です。
    static const Color&     yellow;


#pragma mark - Static 関数

    /// 2つの色の間を Ease-In 補間した色を作成します。
    static Color    EaseIn(const Color& a, const Color& b, float t);
    
    /// 2つの色の間を Ease-In-Out 補間した色を作成します。
    static Color    EaseInOut(const Color& a, const Color& b, float t);

    /// 2つの色の間を Ease-Out 補間した色を作成します。
    static Color    EaseOut(const Color& a, const Color& b, float t);

    /// HSV 色空間の値から RGB 色空間の色を作成します。
    static Color    HSVToRGB(float H, float S, float V);

    /// HSV 色空間の値から RGB 色空間の色を作成します。
    /// hdr フラグが true の場合、各色要素は 0.0〜1.0 の範囲にクランプされません。
    static Color    HSVToRGB(float H, float S, float V, bool hdr);

    /// 2つの色の間を線形補間した色を作成します。パラメーター t は[0, 1]の範囲に制限されます。
    static Color    Lerp(const Color& a, const Color& b, float t);

    /// 2つの色の間を線形補間した色を作成します。パラメーター t の範囲は制限されません。
    static Color    LerpUnclamped(const Color& a, const Color& b, float t);

    /// RGB 色空間の値から HSV 色空間の値を取得します。
    static void     RGBToHSV(const Color& rgbColor, float& outH, float& outS, float& outV);

    /// [a, b]の範囲内でSmoothStepの補完を計算します。
    static Color    SmoothStep(const Color& a, const Color& b, float t);


#pragma mark - メンバ変数

    /// 赤の色成分（0.0〜1.0）
    float   r;

    /// 緑の色成分（0.0〜1.0）
    float   g;

    /// 青の色成分（0.0〜1.0）
    float   b;

    /// アルファの色成分（0.0〜1.0）
    float   a;


#pragma mark - コンストラクタ

    /// コンストラクタ。赤、緑、青の各色成分が 0.0 で、アルファ成分が 1.0 の色を作成します。
    Color();

    /// コンストラクタ。赤、緑、青の各色成分を 0.0〜1.0 で指定して色を作成します。
    Color(float r, float g, float b);

    /// コンストラクタ。赤、緑、青、アルファ値の各色成分を 0.0〜1.0 で指定して色を作成します。
    Color(float r, float g, float b, float a);

    /// コンストラクタ。HTMLで指定するのと同じ色の値を 0xff99cc のような16進数の整数値で指定します。
    Color(const unsigned color);

    /// コンストラクタ。HTMLで指定するのと同じ "ff99cc" のような文字列で色を指定します。
    Color(const std::string& str);
    
    /// コピーコンストラクタ。渡された色と同じ色情報をもつ色を作成します。
    Color(const Color& color);

    /// コンストラクタ。渡されたベクトルを利用して、r=x, g=y, b=z となるように、アルファ成分が 1.0 の色を作成します。
    Color(const Vector3& vec);

    /// コンストラクタ。渡されたベクトルを利用して、r=x, g=y, b=z, a=w となるように色を作成します。
    Color(const Vector4& vec);

    
#pragma mark - Public 関数

    /// 現在の色を元に、アルファ値を指定した値に変更した色を作成します。
    Color   Alpha(float alpha) const;

    /// 現在の色を元に、青の要素を指定した値に変更した色を作成します。
    Color   Blue(float blue) const;

    /// 現在の色を元に、緑の要素を指定した値に変更した色を作成します。
    Color   Green(float green) const;

    /// 現在の色を元に、赤の要素を指定した値に変更した色を作成します。
    Color   Red(float red) const;

    /// ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString() const override;

    /// 各要素に対して適用される書式を指定して、色の各要素を見やすくフォーマットした文字列を返します。
    std::string ToString(const std::string& format) const;

    /// 色の各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str() const override;

    /// 各要素に対して適用される書式を指定して、色の各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str(const std::string& format) const;


#pragma mark - 演算子のオーバーロード

    /// 渡された色情報をこのオブジェクトにコピーします。
    Color&  operator=(const Color& color);

    /// 渡された色の色情報とこのオブジェクトのもつ色情報が等しいかどうかをチェックします。
    bool    operator==(const Color& color) const;

    /// 渡された色の色情報とこのオブジェクトのもつ色情報が等しくないかどうかをチェックします。
    bool    operator!=(const Color& color) const;

    /// operator+=
    Color&  operator+=(const Color& color);

    /// operator-=
    Color&  operator-=(const Color& color);

    /// operator+
    Color   operator+(const Color& color) const;

    /// operator-
    Color   operator-(const Color& color) const;

    /// operator*
    Color   operator*(const Color& color) const;

    /// operator*
    Color   operator*(float value) const;
    
    /// operator/
    Color   operator/(float value) const;

    /// 3次元ベクトルに変換します。
    operator   Vector3() const;

    /// 4次元ベクトルに変換します。
    operator   Vector4() const;
    
};


#endif  //#ifndef __COLOR_HPP__


