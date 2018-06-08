//
//  SimpleDraw.mm
//  MyMetalGame
//
//  Created by numata on 2018/06/08.
//  Copyright © 2018 Satoshi Numata. All rights reserved.
//

#include "SimpleDraw.hpp"
#include "Renderer.hpp"


void FillTriangle(const Vector2 pos[3], const Color& color)
{
    FillTriangle(pos[0], pos[1], pos[2], color, color, color);
}

void FillTriangle(const Vector2 pos[3], const Color color[3])
{
    FillTriangle(pos[0], pos[1], pos[2], color[0], color[1], color[2]);
}

void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& color)
{
    FillTriangle(p1, p2, p3, color, color, color);
}

