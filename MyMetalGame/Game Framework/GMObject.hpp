//
//  GMObject.hpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
//

#ifndef __GM_OBJECT_HPP__
#define __GM_OBJECT_HPP__


#include <string>


/// Game Framework内で扱うすべてのクラス・構造体の基底クラスです。
class GMObject
{
public:
    /// ベクトルの各要素を見やすくフォーマットした文字列を返します。
    virtual std::string ToString() const;

    /// ベクトルの各要素を見やすくフォーマットしたC言語文字列を返します。
    virtual const char* c_str() const;

    /// ベクトルの各要素を見やすくフォーマットした文字列にキャスト変換します。
    operator std::string() const;

    /// ベクトルの各要素を見やすくフォーマットしたC言語文字列にキャスト変換します。
    operator const char*() const;

};


#endif  //#ifndef __GM_OBJECT_HPP__


