//
//  Random.hpp
//  Game Framework
//
//  Created by numata on Aug 05, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__


#include "GMObject.hpp"


/// XorShift法で乱数を生成するクラスです。
class Random : public GMObject
{
public:
    /// 乱数シードを取得します。
    static unsigned GetSeed();

    /// 乱数シードを設定します。
    static void     SetSeed(unsigned seed);

    /// min以上max以下のfloat型の乱数を生成します。
    static float    FloatRange(float min, float max);

    /// 0.0f以上1.0f以下のfloat型の乱数を生成します。
    static float    FloatValue();

    /// min以上max以下の乱数を生成します。
    static int      IntRange(int min, int max);

    /// 0以上INT_MAX未満のint型の乱数を生成します。
    static int      IntValue();

    /// 0以上upper未満のint型の乱数を生成します。
    static int      IntValue(int upper);

    static void     __CleanUp();

private:
    Random() { /* Singleton */ }

};


class XorShift : public GMObject
{
    unsigned firstSeed;
    unsigned x, y, z, w;

public:
	XorShift();

private:
    void        ResetSeed();
    unsigned    Xor128();

public:
    int         NextInt();
    int         NextInt(int upper);
    float       NextFloat();
    double      NextDouble();

    unsigned    GetSeed() const;
    void        SetSeed(unsigned seed0);

};


#endif  //#ifndef __RANDOM_HPP__


