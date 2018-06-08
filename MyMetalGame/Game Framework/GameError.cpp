//
//  GameError.cpp
//  Game Framework
//
//  Created by numata on Jan 03, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "GameError.hpp"
#include <iostream>
#include <execinfo.h>


GameError::GameError() throw()
    : mMessage("Unknown Error")
{
    std::cerr << "🚫 エラー発生：\n　　" << mMessage << std::endl << std::endl;

    std::cerr << "🕒 バックトレース 🕒" << std::endl;
    std::cerr << "🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻" << std::endl;
    void* trace[256];
    int n = backtrace(trace, sizeof(trace) / sizeof(trace[0]));
    backtrace_symbols_fd(trace, n, 2);
    std::cerr << "🔺🔺🔺🔺🔺🔺🔺🔺🔺🔺🔺🔺" << std::endl;
}

GameError::GameError(const char* format, ...) throw()
{
    static char buffer[1024];

    va_list marker;
    va_start(marker, format);
    vsprintf(buffer, format, marker);
    va_end(marker);
    
    mMessage = buffer;

    std::cerr << "🚫 エラー発生：" << mMessage << std::endl << std::endl;

    std::cerr << "🕒 バックトレース 🕒" << std::endl;
    std::cerr << "🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻🔻" << std::endl;
    void* trace[256];
    int n = backtrace(trace, sizeof(trace) / sizeof(trace[0]));
    backtrace_symbols_fd(trace, n, 2);
    std::cerr << "🔺🔺🔺🔺🔺🔺🔺🔺🔺🔺🔺🔺" << std::endl;
}

GameError::GameError(const std::string& message) throw()
    : mMessage(message)
{
    // Do nothing
}

GameError::~GameError() throw()
{
    // Do noghing
}

