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

/// ブレンドモードを表す列挙型
enum BlendMode
{
    /// 未設定のブレンドモード
    BlendModeNone,

    /// アルファ合成のブレンドモード
    BlendModeAlpha,

    /// 加算合成のブレンドモード。Photoshopの「覆い焼き（リニア）」と同等のものです。
    BlendModeAdd,

    /// クリア合成のブレンドモード
    BlendModeClear,

    /// コピー合成のブレンドモード
    BlendModeCopy,

    /// 反転合成のブレンドモード
    BlendModeInvert,

    /// 乗算合成のブレンドモード
    BlendModeMultiply,

    /// スクリーン合成のブレンドモード
    BlendModeScreen,

    /// XOR合成のブレンドモード
    BlendModeXOR,
};

enum DrawCommandType
{
    DrawCommandType_Clear,
    DrawCommandType_SetBlendMode,
    DrawCommandType_FillTriangle,
};

struct DrawCommand
{
    DrawCommandType     type;
    Color               colors[4];
    Vector3             pos[3];
    BlendMode           blendMode;
};

void AddDrawCommand(DrawCommand& command);

extern std::vector<DrawCommand> gDrawCommands;

#endif /* DrawCommand_hpp */
