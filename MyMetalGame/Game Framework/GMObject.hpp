//
//  GMObject.hpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GM_OBJECT_HPP__
#define __GM_OBJECT_HPP__


#include <string>


/// Game Framework内で扱うすべてのクラス・構造体の基底クラスです。
class GMObject
{
public:
    virtual std::string ToString() const;
    virtual const char* c_str() const;

    operator std::string() const;
    operator const char*() const;

};


#endif  //#ifndef __GM_OBJECT_HPP__


