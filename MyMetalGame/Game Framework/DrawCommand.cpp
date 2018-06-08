//
//  DrawCommand.cpp
//  MyMetalGame
//
//  Created by numata on 2018/06/08.
//  Copyright © 2018 Satoshi Numata. All rights reserved.
//

#include "DrawCommand.hpp"


std::vector<DrawCommand> gDrawCommands;


void AddDrawCommand(DrawCommand& command)
{
    gDrawCommands.push_back(command);
}

