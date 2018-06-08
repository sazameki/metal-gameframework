//
//  SimpleDraw.cpp
//  MyMetalGame
//
//  Created by numata on 2018/06/08.
//  Copyright © 2018 Satoshi Numata. All rights reserved.
//

#include "SimpleDraw.hpp"


void Clear(const Color& color)
{
    DrawCommand command;
    command.type = DrawCommandType_Clear;
    command.colors[0] = color;
    AddDrawCommand(command);
}

void SetBlendMode(BlendMode blendMode)
{
    DrawCommand command;
    command.type = DrawCommandType_SetBlendMode;
    command.blendMode = blendMode;
    AddDrawCommand(command);
}

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

void FillTriangle(const Vector2& p1, const Vector2& p2, const Vector2& p3, const Color& c1, const Color& c2, const Color& c3)
{
    DrawCommand command;
    command.type = DrawCommandType_FillTriangle;
    command.pos[0] = p1;
    command.pos[1] = p2;
    command.pos[2] = p3;
    command.colors[0] = c1;
    command.colors[1] = c2;
    command.colors[2] = c3;
    AddDrawCommand(command);
}

