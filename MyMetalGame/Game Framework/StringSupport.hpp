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


/// 指定された書式に従って C++ 文字列を生成します。
std::string FormatString(const char* format, ...);

/// 指定されたパス文字列から最後のパス要素を取り出します。
std::string GetLastPathComponent(const std::string& pathstr);

/// 指定された名前のファイルをバンドルリソースから検索し、フルパスを取得します。
/// ファイルが見つからない場合、空文字列 "" がリターンされます。
std::string GetFilepath(const std::string& filename);

/// separator文字列で指定された文字に基づいて、文字列strを部分文字列に分割します。
std::vector<std::string> Split(const std::string& str, const std::string& separator);

/// strがvalueから始まる文字列かどうかをチェックします。
bool StartsWith(const std::string& str, const std::string& value);

/// strがvalueから始まる文字列かどうかをチェックします。
/// ignoreCase引数にtrueを指定すると、大文字・小文字を無視します。
bool StartsWith(const std::string& str, const std::string& value, bool ignoreCase);

/// strがvalueで終わる文字列かどうかをチェックします。
bool EndsWith(const std::string& str, const std::string& value);

/// strがvalueで終わる文字列かどうかをチェックします。
/// ignoreCase引数にtrueを指定すると、大文字・小文字を無視します。
bool EndsWith(const std::string& str, const std::string& value, bool ignoreCase);

/// 文字列str内の大文字のアルファベットをすべて小文字に変換した文字列を作成します。
std::string ToLower(const std::string& str);

/// 文字列str内の小文字のアルファベットをすべて大文字に変換した文字列を作成します。
std::string ToUpper(const std::string& str);

/// 文字列strの先頭および末尾にある空白文字（タブ文字, 改行文字, 空白文字）をすべて削除します。
std::string Trim(const std::string& str);

/// 文字列strの先頭および末尾から、trimCharsに含まれる文字をすべて削除します。
std::string Trim(const std::string& str, const std::string& trimChars);


#endif  //#ifndef __STRING_SUPPORT_HPP__

