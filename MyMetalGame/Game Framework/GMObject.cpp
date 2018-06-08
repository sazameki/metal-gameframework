//
//  GMObject.cpp
//  Game Framework
//
//  Created by numata on Jan 10, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "GMObject.hpp"
#include "StringSupport.hpp"


static char sDebugStr[256];


std::string GMObject::ToString() const
{
    return FormatString("GMObject(%p)", this);
}

const char* GMObject::c_str() const
{
    std::string str = ToString();
    strcpy(sDebugStr, str.c_str());
    return sDebugStr;
}

GMObject::operator std::string() const
{
    return this->ToString();
}

GMObject::operator const char*() const
{
    return this->c_str();
}

