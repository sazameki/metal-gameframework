//
//  BlendMode.hpp
//  MyMetalGame
//
//  Created by numata on 2018/06/09.
//  Copyright © 2018 Satoshi Numata. All rights reserved.
//

#ifndef BlendMode_hpp
#define BlendMode_hpp


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


#endif /* BlendMode_h */
