//
//  DebugSupport.cpp
//  MyMetalGame
//
//  Created by numata on 2018/06/09.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#include "DebugSupport.hpp"
#include <execinfo.h>
#include <os/log.h>


void AbortGame(const char *format, ...)
{
    static char buffer[1024];
    va_list marker;
    va_start(marker,format);
    vsprintf(buffer, format, marker);
    va_end(marker);

    os_log(OS_LOG_DEFAULT, "<<<< Error >>>> %s", buffer);
    os_log(OS_LOG_DEFAULT, "/--- Backtrace ---\\");
    void* trace[256];
    int n = backtrace(trace, sizeof(trace) / sizeof(trace[0]));
    backtrace_symbols_fd(trace, n, 2);
    exit(-1);
}

