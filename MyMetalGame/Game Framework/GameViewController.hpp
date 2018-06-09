//
//  GameViewController.hpp
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Renderer.hpp"

// Our macOS view controller.
@interface GameViewController : NSViewController
{
    bool    mIsShiftKeyDown;
    int     mShiftKeyState;
}
@end
