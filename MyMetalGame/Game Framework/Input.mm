//
//  Input.mm
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright (c) 2010-2018 Satoshi Numata. All rights reserved.
//

#import "AppDelegate.hpp"
#include "Input.hpp"
#include <algorithm>
#include <utility>
#include "DebugSupport.hpp"


KeyCodeType Input::sKeyState = 0;
KeyCodeType Input::sKeyStateOld = 0;
KeyCodeType Input::sKeyDownStateTriggered = 0;
KeyCodeType Input::sKeyUpStateTriggered = 0;

bool Input::sIsMouseDown = false;
bool Input::sIsMouseDownOld = false;
bool Input::sIsMouseDownTriggered = false;
bool Input::sIsMouseUpTriggered = false;

bool Input::sIsMouseDownRight = false;
bool Input::sIsMouseDownOldRight = false;
bool Input::sIsMouseDownTriggeredRight = false;
bool Input::sIsMouseUpTriggeredRight = false;


const KeyCodeType KeyCode::UpArrow     = (1ULL << 0);
const KeyCodeType KeyCode::DownArrow   = (1ULL << 1);
const KeyCodeType KeyCode::LeftArrow   = (1ULL << 2);
const KeyCodeType KeyCode::RightArrow  = (1ULL << 3);
const KeyCodeType KeyCode::Space  = (1ULL << 4);
const KeyCodeType KeyCode::Escape = (1ULL << 5);
const KeyCodeType KeyCode::Return = (1ULL << 6);
const KeyCodeType KeyCode::Backspace = (1ULL << 7);
const KeyCodeType KeyCode::Delete = (1ULL << 8);
const KeyCodeType KeyCode::Tab = (1ULL << 9);
const KeyCodeType KeyCode::LeftShift  = (1ULL << 10);
const KeyCodeType KeyCode::RightShift  = (1ULL << 11);

const KeyCodeType KeyCode::A      = (1ULL << 15);
const KeyCodeType KeyCode::B      = (1ULL << 16);
const KeyCodeType KeyCode::C      = (1ULL << 17);
const KeyCodeType KeyCode::D      = (1ULL << 18);
const KeyCodeType KeyCode::E      = (1ULL << 19);
const KeyCodeType KeyCode::F      = (1ULL << 20);
const KeyCodeType KeyCode::G      = (1ULL << 21);
const KeyCodeType KeyCode::H      = (1ULL << 22);
const KeyCodeType KeyCode::I      = (1ULL << 23);
const KeyCodeType KeyCode::J      = (1ULL << 24);
const KeyCodeType KeyCode::K      = (1ULL << 25);
const KeyCodeType KeyCode::L      = (1ULL << 26);
const KeyCodeType KeyCode::M      = (1ULL << 27);
const KeyCodeType KeyCode::N      = (1ULL << 28);
const KeyCodeType KeyCode::O      = (1ULL << 29);
const KeyCodeType KeyCode::P      = (1ULL << 30);
const KeyCodeType KeyCode::Q      = (1ULL << 31);
const KeyCodeType KeyCode::R      = (1ULL << 32);
const KeyCodeType KeyCode::S      = (1ULL << 33);
const KeyCodeType KeyCode::T      = (1ULL << 34);
const KeyCodeType KeyCode::U      = (1ULL << 35);
const KeyCodeType KeyCode::V      = (1ULL << 36);
const KeyCodeType KeyCode::W      = (1ULL << 37);
const KeyCodeType KeyCode::X      = (1ULL << 38);
const KeyCodeType KeyCode::Y      = (1ULL << 39);
const KeyCodeType KeyCode::Z      = (1ULL << 40);

const KeyCodeType KeyCode::Alpha0       = (1ULL << 41);
const KeyCodeType KeyCode::Alpha1       = (1ULL << 42);
const KeyCodeType KeyCode::Alpha2       = (1ULL << 43);
const KeyCodeType KeyCode::Alpha3       = (1ULL << 44);
const KeyCodeType KeyCode::Alpha4       = (1ULL << 45);
const KeyCodeType KeyCode::Alpha5       = (1ULL << 46);
const KeyCodeType KeyCode::Alpha6       = (1ULL << 47);
const KeyCodeType KeyCode::Alpha7       = (1ULL << 48);
const KeyCodeType KeyCode::Alpha8       = (1ULL << 49);
const KeyCodeType KeyCode::Alpha9       = (1ULL << 50);

const KeyCodeType KeyCode::Keypad0       = (1ULL << 51);
const KeyCodeType KeyCode::Keypad1       = (1ULL << 52);
const KeyCodeType KeyCode::Keypad2       = (1ULL << 53);
const KeyCodeType KeyCode::Keypad3       = (1ULL << 54);
const KeyCodeType KeyCode::Keypad4       = (1ULL << 55);
const KeyCodeType KeyCode::Keypad5       = (1ULL << 56);
const KeyCodeType KeyCode::Keypad6       = (1ULL << 57);
const KeyCodeType KeyCode::Keypad7       = (1ULL << 58);
const KeyCodeType KeyCode::Keypad8       = (1ULL << 59);
const KeyCodeType KeyCode::Keypad9       = (1ULL << 60);

const KeyCodeType KeyCode::Any    = 0xffffffffffffffffULL;


static const int kAxisHistorySize = 10;
static float xAxisHistory[kAxisHistorySize];
static int xAxisHistoryPos = 0;
static float yAxisHistory[kAxisHistorySize];
static int yAxisHistoryPos = 0;


float Input::GetAxis(const std::string& axisName)
{
    if (axisName == "Horizontal") {
        float x = 0.0f;
        if (Input::GetKey(KeyCode::LeftArrow)) {
            x -= 1.0f;
        }
        if (Input::GetKey(KeyCode::RightArrow)) {
            x += 1.0f;
        }
        xAxisHistory[xAxisHistoryPos++] = x;
        if (xAxisHistoryPos >= kAxisHistorySize) {
            xAxisHistoryPos = 0;
        }
        float average = 0.0f;
        for (int i = 0; i < kAxisHistorySize; i++) {
            average += xAxisHistory[i];
        }
        average /= kAxisHistorySize;
        return average;
    } else if (axisName == "Vertical") {
        float y = 0.0f;
        if (Input::GetKey(KeyCode::DownArrow)) {
            y -= 1.0f;
        }
        if (Input::GetKey(KeyCode::UpArrow)) {
            y += 1.0f;
        }
        yAxisHistory[yAxisHistoryPos++] = y;
        if (yAxisHistoryPos >= kAxisHistorySize) {
            yAxisHistoryPos = 0;
        }
        float average = 0.0f;
        for (int i = 0; i < kAxisHistorySize; i++) {
            average += yAxisHistory[i];
        }
        average /= kAxisHistorySize;
        return average;
    } else {
        AbortGame("Input::GetAxis(): Unknown axis name: %s", axisName.c_str());
        return FLT_MIN;
    }
}

float Input::GetAxisRaw(const std::string& axisName)
{
    if (axisName == "Horizontal") {
        float ret = 0.0f;
        if (Input::GetKey(KeyCode::LeftArrow)) {
            ret -= 1.0f;
        }
        if (Input::GetKey(KeyCode::RightArrow)) {
            ret += 1.0f;
        }
        return ret;
    } else if (axisName == "Vertical") {
        float ret = 0.0f;
        if (Input::GetKey(KeyCode::DownArrow)) {
            ret -= 1.0f;
        }
        if (Input::GetKey(KeyCode::UpArrow)) {
            ret += 1.0f;
        }
        return ret;
    } else {
        AbortGame("Input::GetAxisRaw(): Unknown axis name: %s", axisName.c_str());
        return FLT_MIN;
    }
}

void Input::ResetInputAxes()
{
    for (int i = 0; i < kAxisHistorySize; i++) {
        xAxisHistory[i]= 0.0f;
        yAxisHistory[i]= 0.0f;
    }
}

bool Input::GetKey(KeyCodeType keyMask)
{
    return (sKeyState & keyMask)? true: false;
}

bool Input::GetKeyDown(KeyCodeType keyMask)
{
    return (sKeyDownStateTriggered & keyMask)? true: false;
}

bool Input::GetKeyUp(KeyCodeType keyMask)
{
    return (sKeyUpStateTriggered & keyMask)? true: false;
}


bool Input::GetMouseButton(int button)
{
    if (button == 0) {
        return sIsMouseDown;
    } else {
        return sIsMouseDownRight;
    }
}

bool Input::GetMouseButtonDown(int button)
{
    if (button == 0) {
        return sIsMouseDownTriggered;
    } else {
        return sIsMouseDownTriggeredRight;
    }
}

bool Input::GetMouseButtonUp(int button)
{
    if (button == 0) {
        return sIsMouseUpTriggered;
    } else {
        return sIsMouseUpTriggeredRight;
    }
}

Vector2 Input::MousePosition()
{
    NSWindow* window = [AppDelegate sharedInstance].window;

    NSPoint location = [NSEvent mouseLocation];
    NSRect rect = NSMakeRect(location.x, location.y, 0.0f, 0.0f);
    rect = [window convertRectFromScreen:rect];
    location = rect.origin;
    return Vector2(location.x, location.y);
}

void Input::__ProcessKeyDown(KeyCodeType mask)
{
    sKeyState |= mask;
}

void Input::__ProcessKeyUp(KeyCodeType mask)
{
    sKeyState &= ~mask;
}

void Input::__ProcessMouseDown()
{
    sIsMouseDown = true;
}

void Input::__ProcessMouseUp()
{
    sIsMouseDown = false;
}

void Input::__ProcessMouseDownRight()
{
    sIsMouseDownRight = true;
}

void Input::__ProcessMouseUpRight()
{
    sIsMouseDownRight = false;
}

void Input::__UpdateTriggers()
{
    sKeyDownStateTriggered = sKeyState & ~sKeyStateOld;
    sKeyUpStateTriggered = ~sKeyState & sKeyStateOld;
	sKeyStateOld = sKeyState;
    
    sIsMouseDownTriggered = sIsMouseDown & ~sIsMouseDownOld;
    sIsMouseUpTriggered = ~sIsMouseDown & sIsMouseDownOld;
    sIsMouseDownOld = sIsMouseDown;

    sIsMouseDownTriggeredRight = sIsMouseDownRight & ~sIsMouseDownOldRight;
    sIsMouseUpTriggeredRight = ~sIsMouseDownRight & sIsMouseDownOldRight;
    sIsMouseDownOldRight = sIsMouseDownRight;
}

