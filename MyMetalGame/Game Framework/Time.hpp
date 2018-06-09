//
//  Time.hpp
//  Game Framework
//
//  Created by numata on Jun 26, 2016.
//  Copyright (c) 2016-2018 Satoshi Numata. All rights reserved.
//

#ifndef __TIME_HPP__
#define __TIME_HPP__


/// ゲーム内の時間情報を表す構造体です。
struct Time
{
    /// ゲーム開始から直前のフレームまでに経過したフレーム数
    static int      frameCount;

    /// ゲーム開始から現在のフレームの実行開始までに経過した時間
    static float    time;

    /// 直前のフレームの処理にかかった時間
    static float    deltaTime;

    /// 時間の経過をスケールさせます。デフォルト値は1.0です。
    static float    timeScale;

    /// timeScaleの値によってスケールしない、直前のフレームの処理にかかった時間です。
    static float    unscaledDeltaTime;

    /// timeScaleの値によってスケールしない、ゲーム開始から現在のフレームの実行開始までに経過した時間
    static float    unscaledTime;

    static void     __Update();
};


#endif  //#ifndef __TIME_HPP__

