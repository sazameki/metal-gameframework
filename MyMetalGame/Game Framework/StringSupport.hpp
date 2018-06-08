//
//  StringSupport.hpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __STRING_SUPPORT_HPP__
#define __STRING_SUPPORT_HPP__

#include <string>
#include <vector>


/*!
    @function   FormatString
    @group      System
    @abstract   C++版のsprintf()です。
    指定された書式に従って C++ 文字列を生成します。
 */
std::string FormatString(const char* format, ...);

std::string GetLastPathComponent(const std::string& pathstr);

std::string GetFilepath(const std::string& filename);

/*!
    @function   Split
    @abstract   指定された文字に基づいて文字列を部分文字列に分割します。
 */
std::vector<std::string> Split(const std::string& str, const std::string& separator);

/*!
    @function   StartsWith
    @abstract   指定された文字列から始まる文字列かどうかをチェックします。
 */
bool StartsWith(const std::string& str, const std::string& value);

/*!
    @function   StartsWith
    @abstract   指定された文字列から始まる文字列かどうかをチェックします。
 */
bool StartsWith(const std::string& str, const std::string& value, bool ignoreCase);

/*!
    @function   EndsWith
    @abstract   指定された文字列で終わる文字列かどうかをチェックします。
 */
bool EndsWith(const std::string& str, const std::string& value);

/*!
    @function   EndsWith
    @abstract   指定された文字列で終わる文字列かどうかをチェックします。
 */
bool EndsWith(const std::string& str, const std::string& value, bool ignoreCase);

std::string ToLower(const std::string& str);

std::string ToUpper(const std::string& str);

/*!
    @function   Trim
    @abstract   文字列の先頭および末尾にある空白文字（タブ文字, 改行文字, 空白文字）をすべて削除します。
 */
std::string Trim(const std::string& str);

/*!
    @function   Trim
    @abstract   文字列の先頭および末尾から、指定された文字セットをすべて削除します。
 */
std::string Trim(const std::string& str, const std::string& trimChars);


#endif  //#ifndef __STRING_SUPPORT_HPP__

