//
//  GameViewController.mm
//  MyMetalGame
//
//  Created by numata on 2018/06/05.
//  Copyright (c) 2018 Satoshi Numata. All rights reserved.
//

#import "GameViewController.hpp"
#import "Renderer.hpp"

#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>
#include "Input.hpp"
#include "Globals.hpp"
#import <os/log.h>


@implementation GameViewController
{
    MTKView *_view;

    Renderer *_renderer;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    _view = (MTKView *)self.view;
    _view.device = MTLCreateSystemDefaultDevice();
    if(!_view.device) {
        NSLog(@"Metal is not supported on this device");
        self.view = [[NSView alloc] initWithFrame:self.view.frame];
        return;
    }
    __gMTKView = (__bridge void *)_view;

    // フレームレートの指定
    _view.preferredFramesPerSecond = 60.0;

    _renderer = [[Renderer alloc] initWithMetalKitView:_view];
    [_renderer mtkView:_view drawableSizeWillChange:_view.bounds.size];
    _view.delegate = _renderer;

    // キーボード・マウス処理関係の変数の初期化
    mIsShiftKeyDown = false;
    mShiftKeyState = 0;
}

- (void)keyDown:(NSEvent *)theEvent
{
    unsigned short keyCode = [theEvent keyCode];

    if (keyCode == 0x7e) {
        Input::__ProcessKeyDown(KeyCode::UpArrow);
    }
    else if (keyCode == 0x7d) {
        Input::__ProcessKeyDown(KeyCode::DownArrow);
    }
    else if (keyCode == 0x7b) {
        Input::__ProcessKeyDown(KeyCode::LeftArrow);
    }
    else if (keyCode == 0x7c) {
        Input::__ProcessKeyDown(KeyCode::RightArrow);
    }
    else if (keyCode == 0x00) {
        Input::__ProcessKeyDown(KeyCode::A);
    }
    else if (keyCode == 0x0b) {
        Input::__ProcessKeyDown(KeyCode::B);
    }
    else if (keyCode == 0x08) {
        Input::__ProcessKeyDown(KeyCode::C);
    }
    else if (keyCode == 0x02) {
        Input::__ProcessKeyDown(KeyCode::D);
    }
    else if (keyCode == 0x0e) {
        Input::__ProcessKeyDown(KeyCode::E);
    }
    else if (keyCode == 0x03) {
        Input::__ProcessKeyDown(KeyCode::F);
    }
    else if (keyCode == 0x05) {
        Input::__ProcessKeyDown(KeyCode::G);
    }
    else if (keyCode == 0x04) {
        Input::__ProcessKeyDown(KeyCode::H);
    }
    else if (keyCode == 0x22) {
        Input::__ProcessKeyDown(KeyCode::I);
    }
    else if (keyCode == 0x26) {
        Input::__ProcessKeyDown(KeyCode::J);
    }
    else if (keyCode == 0x28) {
        Input::__ProcessKeyDown(KeyCode::K);
    }
    else if (keyCode == 0x25) {
        Input::__ProcessKeyDown(KeyCode::L);
    }
    else if (keyCode == 0x2e) {
        Input::__ProcessKeyDown(KeyCode::M);
    }
    else if (keyCode == 0x2d) {
        Input::__ProcessKeyDown(KeyCode::N);
    }
    else if (keyCode == 0x1f) {
        Input::__ProcessKeyDown(KeyCode::O);
    }
    else if (keyCode == 0x23) {
        Input::__ProcessKeyDown(KeyCode::P);
    }
    else if (keyCode == 0x0c) {
        Input::__ProcessKeyDown(KeyCode::Q);
    }
    else if (keyCode == 0x0f) {
        Input::__ProcessKeyDown(KeyCode::R);
    }
    else if (keyCode == 0x01) {
        Input::__ProcessKeyDown(KeyCode::S);
    }
    else if (keyCode == 0x11) {
        Input::__ProcessKeyDown(KeyCode::T);
    }
    else if (keyCode == 0x20) {
        Input::__ProcessKeyDown(KeyCode::U);
    }
    else if (keyCode == 0x09) {
        Input::__ProcessKeyDown(KeyCode::V);
    }
    else if (keyCode == 0x0d) {
        Input::__ProcessKeyDown(KeyCode::W);
    }
    else if (keyCode == 0x07) {
        Input::__ProcessKeyDown(KeyCode::X);
    }
    else if (keyCode == 0x10) {
        Input::__ProcessKeyDown(KeyCode::Y);
    }
    else if (keyCode == 0x06) {
        Input::__ProcessKeyDown(KeyCode::Z);
    }
    else if (keyCode == 0x1d) {
        Input::__ProcessKeyDown(KeyCode::Alpha0);
    }
    else if (keyCode == 0x12) {
        Input::__ProcessKeyDown(KeyCode::Alpha1);
    }
    else if (keyCode == 0x13) {
        Input::__ProcessKeyDown(KeyCode::Alpha2);
    }
    else if (keyCode == 0x14) {
        Input::__ProcessKeyDown(KeyCode::Alpha3);
    }
    else if (keyCode == 0x15) {
        Input::__ProcessKeyDown(KeyCode::Alpha4);
    }
    else if (keyCode == 0x17) {
        Input::__ProcessKeyDown(KeyCode::Alpha5);
    }
    else if (keyCode == 0x16) {
        Input::__ProcessKeyDown(KeyCode::Alpha6);
    }
    else if (keyCode == 0x1a) {
        Input::__ProcessKeyDown(KeyCode::Alpha7);
    }
    else if (keyCode == 0x1c) {
        Input::__ProcessKeyDown(KeyCode::Alpha8);
    }
    else if (keyCode == 0x19) {
        Input::__ProcessKeyDown(KeyCode::Alpha9);
    }
    else if (keyCode == 0x31) {
        Input::__ProcessKeyDown(KeyCode::Space);
    }
    else if (keyCode == 0x35) {
        Input::__ProcessKeyDown(KeyCode::Escape);
    }
    else if (keyCode == 0x24 || keyCode == 0x4c) {
        Input::__ProcessKeyDown(KeyCode::Return);
    }
    else if (keyCode == 0x33) {
        Input::__ProcessKeyDown(KeyCode::Backspace);
    }
    else if (keyCode == 0x30) {
        Input::__ProcessKeyDown(KeyCode::Tab);
    }
    else if (keyCode == 0x75) {
        Input::__ProcessKeyDown(KeyCode::Delete);
    }
    else if (keyCode == 0x52) {
        Input::__ProcessKeyDown(KeyCode::Keypad0);
    }
    else if (keyCode == 0x53) {
        Input::__ProcessKeyDown(KeyCode::Keypad1);
    }
    else if (keyCode == 0x54) {
        Input::__ProcessKeyDown(KeyCode::Keypad2);
    }
    else if (keyCode == 0x55) {
        Input::__ProcessKeyDown(KeyCode::Keypad3);
    }
    else if (keyCode == 0x56) {
        Input::__ProcessKeyDown(KeyCode::Keypad4);
    }
    else if (keyCode == 0x57) {
        Input::__ProcessKeyDown(KeyCode::Keypad5);
    }
    else if (keyCode == 0x58) {
        Input::__ProcessKeyDown(KeyCode::Keypad6);
    }
    else if (keyCode == 0x59) {
        Input::__ProcessKeyDown(KeyCode::Keypad7);
    }
    else if (keyCode == 0x5b) {
        Input::__ProcessKeyDown(KeyCode::Keypad8);
    }
    else if (keyCode == 0x5c) {
        Input::__ProcessKeyDown(KeyCode::Keypad9);
    }
    else {
        //printf("非対応のkeyDown: 0x%02x\n", keyCode);
    }
}

- (void)flagsChanged:(NSEvent *)theEvent
{
    NSUInteger modifierFlags = [theEvent modifierFlags];

    if (modifierFlags & NSEventModifierFlagShift) {
        mIsShiftKeyDown = true;
    } else if (mIsShiftKeyDown) {
        mIsShiftKeyDown = false;
    }

    int shiftKeyState = modifierFlags & 0x6;
    if (mIsShiftKeyDown) {
        if (shiftKeyState & 0x2 && !(mShiftKeyState & 0x2)) {
            Input::__ProcessKeyDown(KeyCode::LeftShift);
        }
        if (!(shiftKeyState & 0x2) && (mShiftKeyState & 0x2)) {
            Input::__ProcessKeyUp(KeyCode::LeftShift);
        }
        if (shiftKeyState & 0x4 && !(mShiftKeyState & 0x4)) {
            Input::__ProcessKeyDown(KeyCode::RightShift);
        }
        if (!(shiftKeyState & 0x4) && (mShiftKeyState & 0x4)) {
            Input::__ProcessKeyUp(KeyCode::RightShift);
        }
    } else {
        if (!(shiftKeyState & 0x2) && (mShiftKeyState & 0x2)) {
            Input::__ProcessKeyUp(KeyCode::LeftShift);
        }
        if (!(shiftKeyState & 0x4) && (mShiftKeyState & 0x4)) {
            Input::__ProcessKeyUp(KeyCode::RightShift);
        }
    }

    mShiftKeyState = shiftKeyState;
}

- (void)keyUp:(NSEvent *)theEvent
{
    unsigned short keyCode = [theEvent keyCode];

    if (keyCode == 0x7e) {
        Input::__ProcessKeyUp(KeyCode::UpArrow);
    }
    else if (keyCode == 0x7d) {
        Input::__ProcessKeyUp(KeyCode::DownArrow);
    }
    else if (keyCode == 0x7b) {
        Input::__ProcessKeyUp(KeyCode::LeftArrow);
    }
    else if (keyCode == 0x7c) {
        Input::__ProcessKeyUp(KeyCode::RightArrow);
    }
    else if (keyCode == 0x00) {
        Input::__ProcessKeyUp(KeyCode::A);
    }
    else if (keyCode == 0x0b) {
        Input::__ProcessKeyUp(KeyCode::B);
    }
    else if (keyCode == 0x08) {
        Input::__ProcessKeyUp(KeyCode::C);
    }
    else if (keyCode == 0x02) {
        Input::__ProcessKeyUp(KeyCode::D);
    }
    else if (keyCode == 0x0e) {
        Input::__ProcessKeyUp(KeyCode::E);
    }
    else if (keyCode == 0x03) {
        Input::__ProcessKeyUp(KeyCode::F);
    }
    else if (keyCode == 0x05) {
        Input::__ProcessKeyUp(KeyCode::G);
    }
    else if (keyCode == 0x04) {
        Input::__ProcessKeyUp(KeyCode::H);
    }
    else if (keyCode == 0x22) {
        Input::__ProcessKeyUp(KeyCode::I);
    }
    else if (keyCode == 0x26) {
        Input::__ProcessKeyUp(KeyCode::J);
    }
    else if (keyCode == 0x28) {
        Input::__ProcessKeyUp(KeyCode::K);
    }
    else if (keyCode == 0x25) {
        Input::__ProcessKeyUp(KeyCode::L);
    }
    else if (keyCode == 0x2e) {
        Input::__ProcessKeyUp(KeyCode::M);
    }
    else if (keyCode == 0x2d) {
        Input::__ProcessKeyUp(KeyCode::N);
    }
    else if (keyCode == 0x1f) {
        Input::__ProcessKeyUp(KeyCode::O);
    }
    else if (keyCode == 0x23) {
        Input::__ProcessKeyUp(KeyCode::P);
    }
    else if (keyCode == 0x0c) {
        Input::__ProcessKeyUp(KeyCode::Q);
    }
    else if (keyCode == 0x0f) {
        Input::__ProcessKeyUp(KeyCode::R);
    }
    else if (keyCode == 0x01) {
        Input::__ProcessKeyUp(KeyCode::S);
    }
    else if (keyCode == 0x11) {
        Input::__ProcessKeyUp(KeyCode::T);
    }
    else if (keyCode == 0x20) {
        Input::__ProcessKeyUp(KeyCode::U);
    }
    else if (keyCode == 0x09) {
        Input::__ProcessKeyUp(KeyCode::V);
    }
    else if (keyCode == 0x0d) {
        Input::__ProcessKeyUp(KeyCode::W);
    }
    else if (keyCode == 0x07) {
        Input::__ProcessKeyUp(KeyCode::X);
    }
    else if (keyCode == 0x10) {
        Input::__ProcessKeyUp(KeyCode::Y);
    }
    else if (keyCode == 0x06) {
        Input::__ProcessKeyUp(KeyCode::Z);
    }
    else if (keyCode == 0x1d) {
        Input::__ProcessKeyUp(KeyCode::Alpha0);
    }
    else if (keyCode == 0x12) {
        Input::__ProcessKeyUp(KeyCode::Alpha1);
    }
    else if (keyCode == 0x13) {
        Input::__ProcessKeyUp(KeyCode::Alpha2);
    }
    else if (keyCode == 0x14) {
        Input::__ProcessKeyUp(KeyCode::Alpha3);
    }
    else if (keyCode == 0x15) {
        Input::__ProcessKeyUp(KeyCode::Alpha4);
    }
    else if (keyCode == 0x17) {
        Input::__ProcessKeyUp(KeyCode::Alpha5);
    }
    else if (keyCode == 0x16) {
        Input::__ProcessKeyUp(KeyCode::Alpha6);
    }
    else if (keyCode == 0x1a) {
        Input::__ProcessKeyUp(KeyCode::Alpha7);
    }
    else if (keyCode == 0x1c) {
        Input::__ProcessKeyUp(KeyCode::Alpha8);
    }
    else if (keyCode == 0x19) {
        Input::__ProcessKeyUp(KeyCode::Alpha9);
    }
    else if (keyCode == 0x31) {
        Input::__ProcessKeyUp(KeyCode::Space);
    }
    else if (keyCode == 0x35) {
        Input::__ProcessKeyUp(KeyCode::Escape);
    }
    else if (keyCode == 0x24 || keyCode == 0x4c) {
        Input::__ProcessKeyUp(KeyCode::Return);
    }
    else if (keyCode == 0x33) {
        Input::__ProcessKeyUp(KeyCode::Backspace);
    }
    else if (keyCode == 0x30) {
        Input::__ProcessKeyUp(KeyCode::Tab);
    }
    else if (keyCode == 0x75) {
        Input::__ProcessKeyUp(KeyCode::Delete);
    }
    else if (keyCode == 0x52) {
        Input::__ProcessKeyUp(KeyCode::Keypad0);
    }
    else if (keyCode == 0x53) {
        Input::__ProcessKeyUp(KeyCode::Keypad1);
    }
    else if (keyCode == 0x54) {
        Input::__ProcessKeyUp(KeyCode::Keypad2);
    }
    else if (keyCode == 0x55) {
        Input::__ProcessKeyUp(KeyCode::Keypad3);
    }
    else if (keyCode == 0x56) {
        Input::__ProcessKeyUp(KeyCode::Keypad4);
    }
    else if (keyCode == 0x57) {
        Input::__ProcessKeyUp(KeyCode::Keypad5);
    }
    else if (keyCode == 0x58) {
        Input::__ProcessKeyUp(KeyCode::Keypad6);
    }
    else if (keyCode == 0x59) {
        Input::__ProcessKeyUp(KeyCode::Keypad7);
    }
    else if (keyCode == 0x5b) {
        Input::__ProcessKeyUp(KeyCode::Keypad8);
    }
    else if (keyCode == 0x5c) {
        Input::__ProcessKeyUp(KeyCode::Keypad9);
    }
}

- (void)mouseDown:(NSEvent*)theEvent
{
    Input::__ProcessMouseDown();
}

- (void)mouseUp:(NSEvent*)theEvent
{
    Input::__ProcessMouseUp();
}

- (void)rightMouseDown:(NSEvent*)theEvent
{
    Input::__ProcessMouseDownRight();
}

- (void)rightMouseUp:(NSEvent*)theEvent
{
    Input::__ProcessMouseUpRight();
}

@end
