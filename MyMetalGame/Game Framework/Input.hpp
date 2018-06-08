//
//  Input.hpp
//  Game Framework
//
//  Created by numata on Dec 27, 2010.
//  Copyright (c) 2010-2016 Satoshi Numata. All rights reserved.
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

    /*!
        @const Delete
        deleteキーを表す定数です。
     */
    static const KeyCodeType Delete;

    /*!
        @const Tab
        @group System
        tabキーを表す定数です。
     */
    static const KeyCodeType Tab;

    /*!
        @const LeftShift
        @group System
        左側のshiftキーを表す定数です。
     */
    static const KeyCodeType LeftShift;

    /*!
        @const RightShift
        @group System
        右側のshiftキーを表す定数です。
     */
    static const KeyCodeType RightShift;

    /*!
        @const A
        @group System
        Aキーを表す定数です。
     */
    static const KeyCodeType A;

    /*!
        @const B
        @group System
        Bキーを表す定数です。
     */
    static const KeyCodeType B;

    /*!
        @const C
        @group System
        Cキーを表す定数です。
     */
    static const KeyCodeType C;

    /*!
        @const D
        @group System
        Dキーを表す定数です。
     */
    static const KeyCodeType D;

    /*!
        @const E
        @group System
        Eキーを表す定数です。
     */
    static const KeyCodeType E;

    /*!
        @const F
        @group System
        Fキーを表す定数です。
     */
    static const KeyCodeType F;

    /*!
        @const G
        @group System
        Gキーを表す定数です。
     */
    static const KeyCodeType G;

    /*!
        @const H
        @group System
        Hキーを表す定数です。
     */
    static const KeyCodeType H;

    /*!
        @const I
        @group System
        Iキーを表す定数です。
     */
    static const KeyCodeType I;

    /*!
        @const J
        @group System
        Jキーを表す定数です。
     */
    static const KeyCodeType J;

    /*!
        @const K
        @group System
        Kキーを表す定数です。
     */
    static const KeyCodeType K;

    /*!
        @const L
        @group System
        Lキーを表す定数です。
     */
    static const KeyCodeType L;

    /*!
        @const M
        @group System
        Mキーを表す定数です。
     */
    static const KeyCodeType M;

    /*!
        @const N
        @group System
        Nキーを表す定数です。
     */
    static const KeyCodeType N;

    /*!
        @const O
        @group System
        Oキーを表す定数です。
     */
    static const KeyCodeType O;

    /*!
        @const P
        @group System
        Pキーを表す定数です。
     */
    static const KeyCodeType P;

    /*!
        @const Q
        @group System
        Qキーを表す定数です。
     */
    static const KeyCodeType Q;

    /*!
        @const R
        @group System
        Rキーを表す定数です。
     */
    static const KeyCodeType R;

    /*!
        @const S
        @group System
        Sキーを表す定数です。
     */
    static const KeyCodeType S;

    /*!
        @const T
        @group System
        Tキーを表す定数です。
     */
    static const KeyCodeType T;

    /*!
        @const U
        @group System
        Uキーを表す定数です。
     */
    static const KeyCodeType U;

    /*!
        @const V
        @group System
        Vキーを表す定数です。
     */
    static const KeyCodeType V;

    /*!
        @const W
        @group System
        Wキーを表す定数です。
     */
    static const KeyCodeType W;

    /*!
        @const X
        @group System
        Xキーを表す定数です。
     */
    static const KeyCodeType X;

    /*!
        @const Y
        @group System
        Yキーを表す定数です。
     */
    static const KeyCodeType Y;

    /*!
        @const Z
        @group System
        Zキーを表す定数です。
     */
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


