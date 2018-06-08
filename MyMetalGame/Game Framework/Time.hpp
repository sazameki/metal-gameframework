//
//  Time.hpp
//  Game Framework
//
//  Created by numata on Jun 26, 2016.
//  Copyright (c) 2016 Satoshi Numata. All rights reserved.
//

#ifndef __TIME_HPP__
#define __TIME_HPP__


/// ゲーム内の時間情報を表す構造体です。
struct Time
{
    static int      frameCount;
    static float    time;
    static float    deltaTime;
    static float    timeScale;
    static float    unscaledDeltaTime;
    static float    unscaledTime;

    static void     __Update();
};


#endif  //#ifndef __TIME_HPP__

