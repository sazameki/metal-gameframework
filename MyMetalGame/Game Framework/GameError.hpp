//
//  GameError.hpp
//  Game Framework
//
//  Created by numata on Jan 03, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#ifndef __GAME_ERROR_HPP__
#define __GAME_ERROR_HPP__


#include "GMObject.hpp"
#include <stdexcept>
#include <string>


/*!
    ゲーム実行中のエラーを表す例外クラスです。
 */
class GameError : public std::exception, public GMObject
{
protected:
    std::string     mMessage;
    
public:
    GameError() throw();
    GameError(const char* format, ...) throw();
    GameError(const std::string& message) throw();
    virtual ~GameError() throw();
    
public:
    // TODO: GameError::GetTitle()の文字列をアラートの表示に反映させる。
    virtual std::string GetTitle() const { return "Game Runtime Error"; };
    virtual const char* what() const throw() override { return mMessage.c_str(); };
    
};


#endif  //#ifndef __GAME_ERROR_HPP__


