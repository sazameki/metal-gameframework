//
//  Random.cpp
//  Game Framework
//
//  Created by numata on Aug 05, 2009.
//  Copyright (c) 2009-2016 Satoshi Numata. All rights reserved.
//

#include "Random.hpp"

#include <ctime>
#include <unistd.h>


static unsigned sGeneratedCount = 0;


static XorShift*    sRandomInstance = 0;


unsigned Random::GetSeed()
{
    if (!sRandomInstance) {
        sRandomInstance = new XorShift();
    }
    return sRandomInstance->GetSeed();
}

void Random::SetSeed(unsigned seed)
{
    if (!sRandomInstance) {
        sRandomInstance = new XorShift();
    }
    sRandomInstance->SetSeed(seed);
}

float Random::FloatRange(float min, float max)
{
    return min + FloatValue() * (max - min);
}

float Random::FloatValue()
{
    if (!sRandomInstance) {
        sRandomInstance = new XorShift();
    }
    return sRandomInstance->NextFloat();
}

int Random::IntRange(int min, int max)
{
    if (!sRandomInstance) {
        sRandomInstance = new XorShift();
    }
    return min + sRandomInstance->NextInt(max - min + 1);
}

int Random::IntValue()
{
    if (!sRandomInstance) {
        sRandomInstance = new XorShift();
    }
    return sRandomInstance->NextInt();
}

int Random::IntValue(int upper)
{
    if (!sRandomInstance) {
        sRandomInstance = new XorShift();
    }
    return sRandomInstance->NextInt(upper);
}

void Random::__CleanUp()
{
    if (sRandomInstance) {
        delete sRandomInstance;
        sRandomInstance = 0;
    }
}


XorShift::XorShift()
{
    ResetSeed();
}

void XorShift::ResetSeed()
{
    unsigned the_time = (unsigned)(time(NULL));
    unsigned pid = (unsigned)getpid();
    SetSeed(the_time * pid);
}

unsigned XorShift::Xor128()
{
    sGeneratedCount++;

    unsigned t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    return (w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)));
}

int XorShift::NextInt()
{
    return (int)Xor128();
}

int XorShift::NextInt(int upper)
{
    return (int)(Xor128() % upper);
}

float XorShift::NextFloat()
{
    return ((float)Xor128() / 0xffffffff);
}

double XorShift::NextDouble()
{
    return ((double)Xor128() / 0xffffffff);
}

unsigned XorShift::GetSeed() const
{
    return firstSeed;
}

void XorShift::SetSeed(unsigned seed0)
{
    firstSeed = seed0;

    unsigned seed = firstSeed;

    seed = 1812433253U * (seed ^ (seed >> 30)) + 1;
    x = seed;
    seed = 1812433253U * (seed ^ (seed >> 30)) + 2;
    y = seed;
    seed = 1812433253U * (seed ^ (seed >> 30)) + 3;
    z = seed;
    seed = 1812433253U * (seed ^ (seed >> 30)) + 4;
    w = seed;
}


