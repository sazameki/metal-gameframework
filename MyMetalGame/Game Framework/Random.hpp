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


/*
    @class  Random
    @group  Math
    @abstract 乱数を生成するクラスです。
 
    <p><a href="http://www.jstatsoft.org/v08/i14/" target="_blank">XorShift</a> 法を 128bit で使って、疑似乱数を生成します。</p>
    <p>乱数のシードは、ゲームの起動時に time() 関数（標準C言語ライブラリ）と getpid() 関数（POSIX.1規格）のリターン値を元にして設定されます。デモなどでのシーン再現のために乱数シードを保存する場合には、GetFirstSeed() メソッドを使ってシードを取得し、任意のタイミングで SetFirstSeed() メソッドを使ってシードを設定します。</p>
 */

class Random : public GMObject
{
public:
    static unsigned GetSeed();
    static void     SetSeed(unsigned seed);

    static float    FloatRange(float min, float max);
    static float    FloatValue();

    static int      IntRange(int min, int max);
    static int      IntValue();
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


