//
//  Rect.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
//

#ifndef __RECT_HPP__
#define __RECT_HPP__


#include "GMObject.hpp"

struct Vector2;
struct Vector3;


namespace Game
{
/// 矩形情報を表す構造体です。
struct Rect : public GMObject
{
#pragma mark - Static 関数

    /*!
        MinMaxRect
        @unity-compatible   true
     */
    static Rect     MinMaxRect(float xmin, float ymin, float xmax, float ymax);

    /*!
        NormalizedToPoint
        @unity-compatible   true
     */
    static Vector2  NormalizedToPoint(Rect rectangle, Vector2 normalizedRectCoordinates);

    /*!
        PointToNormalized
        @unity-compatible   true
     */
    static Vector2  PointToNormalized(Rect rectangle, Vector2 point);


#pragma mark - Public 変数

    /// 矩形のx成分
    float  x;

    /// 矩形のy成分
    float  y;

    /// 矩形の横幅
    float  width;

    /// 矩形の高さ
    float  height;


#pragma mark - コンストラクタ

    /// コンストラクタ。矩形情報のすべての要素を0で初期化します。
    Rect();
    
    /// コンストラクタ。x, y, width, heightの要素を指定して初期化します。
    Rect(float x, float y, float width, float height);

    /// コンストラクタ。Vector2構造体で始点posとサイズsizeを指定して初期化します。
    Rect(const Vector2& pos, const Vector2& size);

    /// コピーコンストラクタ
    Rect(const Rect& rect);


#pragma mark - Public 関数

    /// 矩形の中心点の座標を計算します。
    Vector2     Center() const;
    
    /*!
        Contains
     */
    bool        Contains(const Vector2& pos) const;

    /*!
        Contains
     */
    bool        Contains(const Vector3& pos) const;

    /*!
        Contains
     */
    bool        Contains(const Rect& rect) const;
    
    /*!
        Max
     */
    Vector2     Max() const;

    /*!
        Min
     */
    Vector2     Min() const;

    /*!
        Overlaps
     */
    bool        Overlaps(const Rect& rect) const;

    /*!
        Position
     */
    Vector2     Position() const;

    /*!
        Set
     */
    void        Set(float x, float y, float width, float height);

    /*!
        Size
     */
    Vector2     Size() const;

    /*!
        xMax
     */
    float       xMax() const;
    
    /*!
        yMax
     */
    float       yMax() const;
    
    /*!
        xMin
     */
    float       xMin() const;
    
    /*!
        yMin
     */
    float       yMin() const;
    
    /// ベクトルの各要素を見やすくフォーマットした文字列を返します。
    std::string ToString() const override;

    /// 各要素に対して適用される書式を指定して、矩形の各要素を見やすくフォーマットした文字列を返します。
    std::string ToString(const std::string& format) const;

    /// 矩形の各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str() const override;

    /// 各要素に対して適用される書式を指定して、矩形の各要素を見やすくフォーマットしたC言語文字列を返します。
    const char* c_str(const std::string& format) const;


#pragma mark - 演算子のオーバーロード

    /*!
        operator=
     */
    Rect&   operator=(const Rect& rect);
    
    /*!
        operator==
     */
    bool        operator==(const Rect& rect) const;
    
    /*!
        operator!=
     */
    bool        operator!=(const Rect& rect) const;
    
    /*!
        operator+
     */
    Rect        operator+(const Vector2& vec) const;

    /*!
        operator-
     */
    Rect        operator-(const Vector2& vec) const;

    /*!
        operator+=
     */
    Rect&       operator+=(const Vector2& vec);
    
    /*!
        operator-=
     */
    Rect&       operator-=(const Vector2& vec);

};  // struct Rect
    
};  // namespace Game

#endif  //#ifndef __RECT_HPP__

