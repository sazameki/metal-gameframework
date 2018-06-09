//
//  Color.cpp
//  Game Framework
//
//  Created by numata on Dec 26, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
//

#include "Color.hpp"
#include "Types.hpp"
#include "DebugSupport.hpp"
#include "StringSupport.hpp"
#include "Globals.hpp"

#include <cmath>
#include <cstdlib>


#pragma mark - 色の定数

const Color& Color::black       = Color(0.0f, 0.0f, 0.0f, 1.0f);
const Color& Color::white       = Color(1.0f, 1.0f, 1.0f, 1.0f);
const Color& Color::clear       = Color(0.0f, 0.0f, 0.0f, 0.0f);

const Color& Color::blue        = Color(0.0f, 0.0f, 1.0f, 1.0f);
const Color& Color::cyan        = Color(0.0f, 1.0f, 1.0f, 1.0f);
const Color& Color::gray        = Color(0.5f, 0.5f, 0.5f, 1.0f);
const Color& Color::green       = Color(0.0f, 1.0f, 0.0f, 1.0f);
const Color& Color::orange      = Color(1.0f, 0.5f, 0.0f, 1.0f);
const Color& Color::pink        = Color(1.0f, 0.25f, 0.6f, 1.0f);
const Color& Color::purple      = Color(1.0f, 0.0f, 1.0f, 1.0f);
const Color& Color::red         = Color(1.0f, 0.0f, 0.0f, 1.0f);
const Color& Color::yellow      = Color(1.0f, 1.0f, 0.0f, 1.0f);

const Color& Color::lightblue   = Color(0.5f, 0.5f, 1.0f, 1.0f);
const Color& Color::lightcyan   = Color(0.65f, 1.0f, 1.0f, 1.0f);
const Color& Color::lightgray   = Color(0.75f, 0.75f, 0.75f, 1.0f);
const Color& Color::lightgreen  = Color(0.5f, 1.0f, 0.5f, 1.0f);
const Color& Color::lightorange = Color(1.0f, 0.75f, 0.5f, 1.0f);
const Color& Color::lightpink   = Color(1.0f, 0.5f, 0.8f, 1.0f);
const Color& Color::lightpurple = Color(1.0f, 0.5f, 1.0f, 1.0f);
const Color& Color::lightred    = Color(1.0f, 0.5f, 0.5f, 1.0f);
const Color& Color::lightyellow = Color(1.0f, 1.0f, 0.65f, 1.0f);

const Color& Color::darkblue    = Color(0.0f, 0.0f, 0.7f, 1.0f);
const Color& Color::darkcyan    = Color(0.0f, 0.5f, 0.5f, 1.0f);
const Color& Color::darkgray    = Color(0.25f, 0.25f, 0.25f, 1.0f);
const Color& Color::darkgreen   = Color(0.0f, 0.5f, 0.0f, 1.0f);
const Color& Color::darkorange  = Color(0.5f, 0.25f, 0.0f, 1.0f);
const Color& Color::darkpink    = Color(0.6f, 0.08f, 0.3f, 1.0f);
const Color& Color::darkpurple  = Color(0.5f, 0.0f, 0.5f, 1.0f);
const Color& Color::darkred     = Color(0.6f, 0.0f, 0.0f, 1.0f);
const Color& Color::darkyellow  = Color(0.5f, 0.5f, 0.0f, 1.0f);


#pragma mark - Static 関数

Color Color::EaseIn(const Color& c1, const Color& c2, float t)
{
    t = Mathf::Clamp01(t);
    t *= t;
    
    return Color(c1.r + (c2.r - c1.r) * t,
                 c1.g + (c2.g - c1.g) * t,
                 c1.b + (c2.b - c1.b) * t,
                 c1.a + (c2.a - c1.a) * t);
}

Color Color::EaseInOut(const Color& c1, const Color& c2, float t)
{
    t = Mathf::Clamp01(t);

    float rm = (c1.r + c2.r) / 2;
    float gm = (c1.g + c2.g) / 2;
    float bm = (c1.b + c2.b) / 2;
    float am = (c1.a + c2.a) / 2;

    t *= 2;
    if (t <= 1.0f) {
        t *= t;
        return Color(c1.r + (rm - c1.r) * t,
                     c1.g + (gm - c1.g) * t,
                     c1.b + (bm - c1.b) * t,
                     c1.a + (am - c1.a) * t);
    }
    t -= 1;
    t *= t - 2;
    return Color(rm - (c2.r - rm) * t,
                 gm - (c2.g - gm) * t,
                 bm - (c2.b - bm) * t,
                 am - (c2.a - am) * t);
}

Color Color::EaseOut(const Color& c1, const Color& c2, float t)
{
    t = Mathf::Clamp01(t);
    t *= (t - 2);
    
    return Color(c1.r - (c2.r - c1.r) * t,
                 c1.g - (c2.g - c1.g) * t,
                 c1.b - (c2.b - c1.b) * t,
                 c1.a - (c2.a - c1.a) * t);
}

Color Color::HSVToRGB(float H, float S, float V)
{
    return Color::HSVToRGB(H, S, V, false);
}

Color Color::HSVToRGB(float H, float S, float V, bool hdr)
{
    if (!hdr) {
        H = Mathf::Clamp01(H);
        S = Mathf::Clamp01(S);
        V = Mathf::Clamp01(V);
    }
    if (S == 0.0f) {
        return Color(V, V, V);
    }
    H *= 6.0f;
    int i = (int)floorf(H);
    float F = H - i;
    float M = V * (1.0f - S);
    float N = V * (1.0f - S * F);
    float K = V * (1.0f - S * (1.0f - F));
    switch (i) {
        case 0:
            return Color(V, K, M);
        case 1:
            return Color(N, V, M);
        case 2:
            return Color(M, V, K);
        case 3:
            return Color(M, N, V);
        case 4:
            return Color(K, M, V);
        default:
            return Color(V, M, N);
    }
}

Color Color::Lerp(const Color& a, const Color& b, float t)
{
    t = Mathf::Clamp01(t);

    return Color(a.r + (b.r - a.r) * t,
                 a.g + (b.g - a.g) * t,
                 a.b + (b.b - a.b) * t,
                 a.a + (b.a - a.a) * t);
}

Color Color::LerpUnclamped(const Color& a, const Color& b, float t)
{
    return Color(a.r + (b.r - a.r) * t,
                 a.g + (b.g - a.g) * t,
                 a.b + (b.b - a.b) * t,
                 a.a + (b.a - a.a) * t);
}

void Color::RGBToHSV(const Color& rgbColor, float& outH, float& outS, float& outV)
{
    float max = std::max(std::max(rgbColor.r, rgbColor.g), rgbColor.b);
    float min = std::min(std::min(rgbColor.r, rgbColor.g), rgbColor.b);
    outV = max;
    if (max == rgbColor.r) {
        outH = 60 * (rgbColor.g - rgbColor.b) / (max - min);
    } else if (max == rgbColor.g) {
        outH = 60 * (rgbColor.b - rgbColor.r) / (max - min) + 120;
    } else {
        outH = 60 * (rgbColor.r - rgbColor.g) / (max - min) + 240;
    }
    outS = (max - min) / max;
}

Color Color::SmoothStep(const Color& a, const Color& b, float t)
{
    Vector4 v = Vector4::SmoothStep(a, b, t);
    return Color(Mathf::Clamp01(v.x), Mathf::Clamp01(v.y), Mathf::Clamp01(v.z), Mathf::Clamp01(v.w));
}


#pragma mark - コンストラクタ

Color::Color()
    : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
{
    // Do nothing
}

Color::Color(float r_, float g_, float b_)
    : r(r_), g(g_), b(b_), a(1.0f)
{
    // Do nothing
}

Color::Color(float r_, float g_, float b_, float a_)
    : r(r_), g(g_), b(b_), a(a_)
{
    // Do nothing
}

Color::Color(const unsigned color)
{
    __gGMLastErrorPlace = "Color::Color()";

    r = ((color >> 16) & 0xff) / 255.0f;
    g = ((color >> 8) & 0xff) / 255.0f;
    b = (color & 0xff) / 255.0f;
    a = 1.0f;
}

Color::Color(const std::string& str)
{
    __gGMLastErrorPlace = "Color::Color()";

    int length = (int)str.length();
    if (length == 3) {
        int red = (int)strtol(str.substr(0, 1).c_str(), NULL, 16);
        int green = (int)strtol(str.substr(1, 1).c_str(), NULL, 16);
        int blue = (int)strtol(str.substr(2, 1).c_str(), NULL, 16);
        r = red / 15.0f;
        g = green / 15.0f;
        b = blue / 15.0f;
    } else if (length == 6) {
        int red = (int)strtol(str.substr(0, 2).c_str(), NULL, 16);
        int green = (int)strtol(str.substr(2, 2).c_str(), NULL, 16);
        int blue = (int)strtol(str.substr(4, 2).c_str(), NULL, 16);
        r = red / 255.0f;
        g = green / 255.0f;
        b = blue / 255.0f;
    } else {
        AbortGame("不正なカラー指定文字列です \"%s\"", str.c_str());
    }
    a = 1.0f;
}

Color::Color(const Color& color)
    : r(color.r), g(color.g), b(color.b), a(color.a)
{
    // Do nothing
}

Color::Color(const Vector3& vector)
    : a(1.0f)
{
    r = Mathf::Clamp01(vector.x);
    g = Mathf::Clamp01(vector.y);
    b = Mathf::Clamp01(vector.z);
}

Color::Color(const Vector4& vector)
{
    r = Mathf::Clamp01(vector.x);
    g = Mathf::Clamp01(vector.y);
    b = Mathf::Clamp01(vector.z);
    a = Mathf::Clamp01(vector.w);
}


#pragma mark - Public 関数

Color Color::Alpha(float alpha) const
{
    Color ret(*this);
    ret.a = alpha;
    return ret;
}

Color Color::Blue(float blue) const
{
    Color ret(*this);
    ret.b = blue;
    return ret;
}

Color Color::Green(float green) const
{
    Color ret(*this);
    ret.g = green;
    return ret;
}

Color Color::Red(float red) const
{
    Color ret(*this);
    ret.r = red;
    return ret;
}


std::string Color::ToString() const
{
    return ToString("%.3f");
}

std::string Color::ToString(const std::string& format) const
{
    std::string rStr = FormatString(format.c_str(), r);
    std::string gStr = FormatString(format.c_str(), g);
    std::string bStr = FormatString(format.c_str(), b);
    std::string aStr = FormatString(format.c_str(), a);
    return FormatString("RGBA(%s, %s, %s, %s)", rStr.c_str(), gStr.c_str(), bStr.c_str(), aStr.c_str());
}

const char* Color::c_str() const
{
    return GMObject::c_str();
}

const char* Color::c_str(const std::string& format) const
{
    return ToString(format).c_str();
}


#pragma mark - 演算子のオーバーロード

Color& Color::operator=(const Color& color)
{
    r = color.r;
    g = color.g;
    b = color.b;
    a = color.a;
    return *this;
}

bool Color::operator==(const Color& color) const
{
    if (fabsf(r - color.r) >= 9.99999944E-11f) return false;
    if (fabsf(g - color.g) >= 9.99999944E-11f) return false;
    if (fabsf(b - color.b) >= 9.99999944E-11f) return false;
    if (fabsf(a - color.a) >= 9.99999944E-11f) return false;
    return true;
}

bool Color::operator!=(const Color& color) const
{
    if (fabsf(r - color.r) >= 9.99999944E-11f) return true;
    if (fabsf(g - color.g) >= 9.99999944E-11f) return true;
    if (fabsf(b - color.b) >= 9.99999944E-11f) return true;
    if (fabsf(a - color.a) >= 9.99999944E-11f) return true;
    return false;
}

Color& Color::operator+=(const Color& color)
{
    *this = *this + color;
    return *this;
}

Color& Color::operator-=(const Color& color)
{
    *this = *this - color;
    return *this;
}

Color Color::operator+(const Color& color) const
{
    return Color(r + color.r, g + color.g, b + color.b, a + color.a);
}

Color Color::operator-(const Color& color) const
{
    return Color(r - color.r, g - color.g, b - color.b, a - color.a);
}

Color Color::operator*(const Color& color) const
{
    return Color(r * color.r, g * color.g, b * color.b, a * color.a);
}

Color Color::operator*(float value) const
{
    return Color(r * value, g * value, b * value, a * value);
}

Color Color::operator/(float value) const
{
    return Color(r / value, g / value, b / value, a / value);
}

Color::operator Vector3() const
{
    return Vector3(r, g, b);
}

Color::operator Vector4() const
{
    return Vector4(r, g, b, a);
}


