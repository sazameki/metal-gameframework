//
//  SimpleDraw.hpp
//  MyMetalGame
//
//  Created by numata on 2018/06/08.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#ifndef SimpleDraw_hpp
#define SimpleDraw_hpp

#include "Color.hpp"
#include "Vector2.hpp"
#include "BlendMode.hpp"


void    Clear(const Color& color);

void    SetBlendMode(BlendMode blendMode);

void    FillTriangle(const Vector2 pos[3], const Color& color);
void    FillTriangle(const Vector2 pos[3], const Color color[3]);
void    FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color);
void    FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& c1, const Color& c2, const Color& c3);

#endif /* SimpleDraw_hpp */
