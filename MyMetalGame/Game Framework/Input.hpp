//
//  Input.hpp
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright (c) 2010-2018 Satoshi Numata. All rights reserved.
//


#ifndef __INPUT_HPP__
#define __INPUT_HPP__

#include "GMObject.hpp"
#include "Types.hpp"
#include <map>
#include <set>


// 64キーまでサポート
typedef unsigned long long  KeyCodeType;


struct KeyCode
{
    /// 上向きの矢印キーを表す定数です。
    static const KeyCodeType UpArrow;

    /// 下向きの矢印キーを表す定数です。
    static const KeyCodeType DownArrow;

    /// 左向きの矢印キーを表す定数です。
    static const KeyCodeType LeftArrow;

    /// 右向きの矢印キーを表す定数です。
    static const KeyCodeType RightArrow;

    /// スペースキーを表す定数です。
    static const KeyCodeType Space;

    /// escキーを表す定数です。
    static const KeyCodeType Escape;

    /// returnキーを表す定数です。
    static const KeyCodeType Return;

    /// backspaceキーを表す定数です。
    static const KeyCodeType Backspace;

    /// deleteキーを表す定数です。
    static const KeyCodeType Delete;

    /// tabキーを表す定数です。
    static const KeyCodeType Tab;

    /// 左側のshiftキーを表す定数です。
    static const KeyCodeType LeftShift;

    /// 右側のshiftキーを表す定数です。
    static const KeyCodeType RightShift;

    /// Aキーを表す定数です。
    static const KeyCodeType A;

    /// Bキーを表す定数です。
    static const KeyCodeType B;

    /// Cキーを表す定数です。
    static const KeyCodeType C;

    /// Dキーを表す定数です。
    static const KeyCodeType D;

    /// Eキーを表す定数です。
    static const KeyCodeType E;

    /// Fキーを表す定数です。
    static const KeyCodeType F;

    /// Gキーを表す定数です。
    static const KeyCodeType G;

    /// Hキーを表す定数です。
    static const KeyCodeType H;

    /// Iキーを表す定数です。
    static const KeyCodeType I;

    /// Jキーを表す定数です。
    static const KeyCodeType J;

    /// Kキーを表す定数です。
    static const KeyCodeType K;

    /// Lキーを表す定数です。
    static const KeyCodeType L;

    /// Mキーを表す定数です。
    static const KeyCodeType M;

    /// Nキーを表す定数です。
    static const KeyCodeType N;

    /// Oキーを表す定数です。
    static const KeyCodeType O;

    /// Pキーを表す定数です。
    static const KeyCodeType P;

    /// Qキーを表す定数です。
    static const KeyCodeType Q;

    /// Rキーを表す定数です。
    static const KeyCodeType R;

    /// Sキーを表す定数です。
    static const KeyCodeType S;

    /// Tキーを表す定数です。
    static const KeyCodeType T;

    /// Uキーを表す定数です。
    static const KeyCodeType U;

    /// Vキーを表す定数です。
    static const KeyCodeType V;

    /// Wキーを表す定数です。
    static const KeyCodeType W;

    /// Xキーを表す定数です。
    static const KeyCodeType X;

    /// Yキーを表す定数です。
    static const KeyCodeType Y;

    /// Zキーを表す定数です。
    static const KeyCodeType Z;

    /// アルファベット列の上にある数字の0キーを表す定数です。
    static const KeyCodeType Alpha0;

    /// アルファベット列の上にある数字の1キーを表す定数です。
    static const KeyCodeType Alpha1;

    /// アルファベット列の上にある数字の2キーを表す定数です。
    static const KeyCodeType Alpha2;

    /// アルファベット列の上にある数字の3キーを表す定数です。
    static const KeyCodeType Alpha3;
    
    /// アルファベット列の上にある数字の4キーを表す定数です。
    static const KeyCodeType Alpha4;
    
    /// アルファベット列の上にある数字の5キーを表す定数です。
    static const KeyCodeType Alpha5;
    
    /// アルファベット列の上にある数字の6キーを表す定数です。
    static const KeyCodeType Alpha6;
    
    /// アルファベット列の上にある数字の7キーを表す定数です。
    static const KeyCodeType Alpha7;
    
    /// アルファベット列の上にある数字の8キーを表す定数です。
    static const KeyCodeType Alpha8;
    
    /// アルファベット列の上にある数字の9キーを表す定数です。
    static const KeyCodeType Alpha9;

    /// テンキーの0を表す定数です。
    static const KeyCodeType Keypad0;
    
    /// テンキーの1を表す定数です。
    static const KeyCodeType Keypad1;
    
    /// テンキーの2を表す定数です。
    static const KeyCodeType Keypad2;
    
    /// テンキーの3を表す定数です。
    static const KeyCodeType Keypad3;
    
    /// テンキーの4を表す定数です。
    static const KeyCodeType Keypad4;
    
    /// テンキーの5を表す定数です。
    static const KeyCodeType Keypad5;
    
    /// テンキーの6を表す定数です。
    static const KeyCodeType Keypad6;
    
    /// テンキーの7を表す定数です。
    static const KeyCodeType Keypad7;
    
    /// テンキーの8を表す定数です。
    static const KeyCodeType Keypad8;
    
    /// テンキーの9を表す定数です。
    static const KeyCodeType Keypad9;

    /// あらゆるキーのマスクを表す定数です。
    static const KeyCodeType Any;

    // TODO: マウスをマスク定数でサポートする。
};


/// キーボードとマウスの入力を管理するためのクラスです。
class Input : public GMObject
{
    static KeyCodeType  sKeyState;
    static KeyCodeType  sKeyStateOld;
    static KeyCodeType  sKeyDownStateTriggered;
    static KeyCodeType  sKeyUpStateTriggered;
    
    static bool         sIsMouseDown;
    static bool         sIsMouseDownOld;
    static bool         sIsMouseDownTriggered;
    static bool         sIsMouseUpTriggered;
    
    static bool         sIsMouseDownRight;
    static bool         sIsMouseDownOldRight;
    static bool         sIsMouseDownTriggeredRight;
    static bool         sIsMouseUpTriggeredRight;

public:
    static float    GetAxis(const std::string& axisName);
    static float    GetAxisRaw(const std::string& axisName);
    static void     ResetInputAxes();


#pragma mark - キーボードの管理
public:
    /// キーボードの状態を確認します。
    static bool     GetKey(KeyCodeType keyMask);

    /// キーボードの状態を確認し、直前のフレームでキーが押されたかどうかをリターンします。
    static bool     GetKeyDown(KeyCodeType keyMask);

    /// キーボードの状態を確認し、直前のフレームでキーが離されたかどうかをリターンします。
    static bool     GetKeyUp(KeyCodeType keyMask);


#pragma mark - マウスの管理
public:

    /// マウスボタンの状態を確認します。
    static bool     GetMouseButton(int button);

    /// マウスボタンの状態を確認し、直前のフレームでボタンが押されたかどうかをリターンします。
    static bool     GetMouseButtonDown(int button);

    /// マウスボタンの状態を確認し、直前のフレームでボタンが離されたかどうかをリターンします。
    static bool     GetMouseButtonUp(int button);
    
    /// マウスの現在のカーソル位置を取得します。
    static Vector2  MousePosition();


public:
    static void __ProcessKeyDown(KeyCodeType mask);
    static void __ProcessKeyUp(KeyCodeType mask);
    static void __ProcessMouseDown();
    static void __ProcessMouseUp();
    static void __ProcessMouseDownRight();
    static void __ProcessMouseUpRight();
    static void __UpdateTriggers();
};


#endif  //#ifndef __INPUT_HPP__


