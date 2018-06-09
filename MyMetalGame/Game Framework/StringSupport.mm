//
//  StringSupport.mm
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2018 Satoshi Numata. All rights reserved.
//

#include "StringSupport.hpp"
#include <iostream>
#include <string>
#include <sstream>

#import <Foundation/Foundation.h>


std::string FormatString(const char* format, ...)
{
    static char buffer[1024];
    va_list marker;
    va_start(marker,format);
    vsprintf(buffer, format, marker);
    va_end(marker);
    return buffer;
}

std::string GetLastPathComponent(const std::string& pathstr)
{
    NSString *str = [[NSString alloc] initWithCString:pathstr.c_str() encoding:NSUTF8StringEncoding];
    std::string ret = [[str lastPathComponent] cStringUsingEncoding:NSUTF8StringEncoding];
    return ret;
}

std::string GetFilepath(const std::string& filename)
{
    NSString *fileNameObj = [[NSString alloc] initWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
    
    NSString *body = [fileNameObj stringByDeletingPathExtension];
    NSString *ext = [fileNameObj pathExtension];

    NSBundle* bundle = [NSBundle mainBundle];
    NSString *path = [bundle pathForResource:body ofType:ext];
    
    if (!path) {
        return "";
    }
    
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}

std::vector<std::string> Split(const std::string& str, const std::string& separator)
{
    std::vector<std::string> ret;
    
    std::string::size_type pos = str.find_first_not_of(separator);

    while (pos != std::string::npos) {
        std::string::size_type p = str.find_first_of(separator, pos);
        if (p == std::string::npos) {
            std::string::size_type lastSize = str.length();
            if (lastSize > 0) {
                std::string part = str.substr(pos, lastSize);
                ret.push_back(part);
            }
            break;
        }
        std::string part = str.substr(pos, p - pos);
        ret.push_back(part);
        pos = str.find_first_not_of(separator, p + 1);
    }
    return ret;
}

bool StartsWith(const std::string& str, const std::string& value)
{
    return StartsWith(str, value, true);
}

bool StartsWith(const std::string& str, const std::string& value, bool ignoreCase)
{
    auto length = value.size();
    if (str.length() < length) {
        return false;
    }
    
    std::string sub = str.substr(0, length);
    if (ignoreCase) {
        return (strncasecmp(sub.c_str(), value.c_str(), length) == 0);
    } else {
        return (sub == value);
    }
}

bool EndsWith(const std::string& str, const std::string& value)
{
    return EndsWith(str, value, true);
}

bool EndsWith(const std::string& str, const std::string& value, bool ignoreCase)
{
    auto length = value.size();
    if (str.length() < length) {
        return false;
    }

    std::string sub = str.substr(str.length()-length, length);
    if (ignoreCase) {
        return (strncasecmp(sub.c_str(), value.c_str(), length) == 0);
    } else {
        return (sub == value);
    }
}

std::string ToLower(const std::string& str)
{
    std::string ret;
    ret.resize(str.length());
    std::transform(str.cbegin(), str.cend(), ret.begin(), ::tolower);
    return ret;
}

std::string ToUpper(const std::string& str)
{
    std::string ret;
    ret.resize(str.length());
    std::transform(str.cbegin(), str.cend(), ret.begin(), ::toupper);
    return ret;
}

std::string Trim(const std::string& str)
{
    return Trim(str, "\t\r\n ");
}

std::string Trim(const std::string& str, const std::string& trimChars)
{
    std::string::size_type left = str.find_first_not_of(trimChars);
    
    if (left == std::string::npos) {
        return str;
    }
    std::string::size_type right = str.find_last_not_of(trimChars);
    return str.substr(left, right - left + 1);
}

