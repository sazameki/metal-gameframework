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

    /// X方向・Y方向ともに最小値と最大値を指定して、矩形情報を作成します。
    static Rect     MinMaxRect(float xmin, float ymin, float xmax, float ymax);

    /// 正規化座標を指定して矩形内での位置を返します。
    static Vector2  NormalizedToPoint(const Rect& rect, const Vector2& normalizedRectCoordinates);

    /// 指定された座標に対応する正規化座標を返します。
    static Vector2  PointToNormalized(const Rect& rect, const Vector2& point);


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

    /// 指定した点がこの矩形内に含まれるかどうかを計算します。
    bool        Contains(const Vector2& pos) const;

    /// 指定した点がこの矩形内に含まれるかどうかを計算します。Z座標は無視されます。
    bool        Contains(const Vector3& pos) const;

    /// 指定した矩形がこの矩形内に含まれるかどうかを計算します。
    bool        Contains(const Rect& rect) const;
    
    /// X座標・Y座標ともにこの矩形の最大の値をもつ座標をリターンします。
    Vector2     Max() const;

    /// X座標・Y座標ともにこの矩形の最小の値をもつ座標をリターンします。
    Vector2     Min() const;

    /// 矩形同士が重なっているかどうかを計算します。
    bool        Overlaps(const Rect& rect) const;

    /// この矩形の始点座標をVector2としてリターンします。
    Vector2     Position() const;

    /// この矩形の各要素を個別に設定します。
    void        Set(float x, float y, float width, float height);

    /// この矩形のサイズ情報をVector2としてリターンします。
    Vector2     Size() const;

    /// この矩形のX方向の最大値をリターンします。
    float       xMax() const;

    /// この矩形のY方向の最大値をリターンします。
    float       yMax() const;
    
    /// この矩形のX方向の最小値をリターンします。
    float       xMin() const;
    
    /// この矩形のY方向の最小値をリターンします。
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

    /// この矩形に矩形rectの内容をコピーします。
    Rect&       operator=(const Rect& rect);
    
    /// この矩形の始点座標にベクトルvecの値を足し合わせた矩形を作成します。
    Rect        operator+(const Vector2& vec) const;

    /// この矩形の始点座標からベクトルvecの値を引いた矩形を作成します。
    Rect        operator-(const Vector2& vec) const;

    /// この矩形の始点座標にベクトルvecの値を足し合わせます。
    Rect&       operator+=(const Vector2& vec);
    
    /// この矩形の始点座標からベクトルvecの値を引きます。
    Rect&       operator-=(const Vector2& vec);

    /// 与えられた矩形がこの矩形と等しいかを判定します。
    bool        operator==(const Rect& rect) const;

    /// 与えられた矩形がこの矩形と等しくないかを判定します。
    bool        operator!=(const Rect& rect) const;


};  // struct Rect
    
};  // namespace Game

#endif  //#ifndef __RECT_HPP__

