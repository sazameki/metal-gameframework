//
//  DrawCommand.hpp
//  MyMetalGame
//
//  Created by numata on 2018/06/08.
//  Copyright © 2018 Satoshi Numata. All rights reserved.
//

#ifndef DrawCommand_hpp
#define DrawCommand_hpp

#include <vector>
#include "Color.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"

enum DrawCommandType
{
    DrawCommandType_FillTriangle,
};

struct DrawCommand
{
    DrawCommandType     type;
    Color               colors[4];
    Vector3             pos[3];
};

void AddDrawCommand(DrawCommand& command);

extern std::vector<DrawCommand> gDrawCommands;

#endif /* DrawCommand_hpp */
