//
//  Time.cpp
//  Game Framework
//
//  Created by numata on Jun 26, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#include "Time.hpp"
#include <sys/time.h>


static double   sStartTime = -1.0;
static double   sCurrentTime = -1.0;


static double GetCurrentTime()
{
    static timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;
}


int Time::frameCount = 0;
float Time::time = 0.0f;
float Time::deltaTime = 0.0f;
float Time::timeScale = 1.0f;
float Time::unscaledDeltaTime = 0.0f;
float Time::unscaledTime = 0.0f;


void Time::__Update()
{
    if (sStartTime < 0.0) {
        sStartTime = GetCurrentTime();
        sCurrentTime = sStartTime;
    }
    double prevTime = sCurrentTime;
    sCurrentTime = GetCurrentTime();

    unscaledDeltaTime = (float)(sCurrentTime - prevTime);
    deltaTime = unscaledDeltaTime * timeScale;
    
    time += deltaTime;
    unscaledTime += unscaledDeltaTime;
}

