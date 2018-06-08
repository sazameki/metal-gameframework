//
//  Rect.cpp
//  Game Framework
//
//  Created by numata on Jan 02, 2011.
//  Copyright (c) 2011-2016 Satoshi Numata. All rights reserved.
//

#include "Rect.hpp"

#include "Mathf.hpp"
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "StringSupport.hpp"

#include <algorithm>
#include <cmath>


using namespace Game;


#pragma mark - Static 関数

Rect Rect::MinMaxRect(float xmin, float ymin, float xmax, float ymax)
{
    return Rect(xmin, ymin, xmax - xmin, ymax - ymin);
}

Vector2 Rect::NormalizedToPoint(Rect rectangle, Vector2 normalizedRectCoordinates)
{
    return Vector2(Mathf::Lerp(rectangle.x, rectangle.xMax(), normalizedRectCoordinates.x),
                   Mathf::Lerp(rectangle.y, rectangle.yMax(), normalizedRectCoordinates.y));
}

Vector2 Rect::PointToNormalized(Rect rectangle, Vector2 point)
{
    return Vector2(Mathf::InverseLerp(rectangle.x, rectangle.xMax(), point.x),
                   Mathf::InverseLerp(rectangle.y, rectangle.yMax(), point.y));
}


#pragma mark - コンストラクタ

Rect::Rect()
    : x(0.0f), y(0.0f), width(0.0f), height(0.0f)
{
    // Do nothing
}

Rect::Rect(float x_, float y_, float width_, float height_)
    : x(x_), y(y_), width(width_), height(height_)
{
    // Do nothing
}

Rect::Rect(const Vector2& pos, const Vector2& size)
    : x(pos.x), y(pos.y), width(size.x), height(size.y)
{
    // Do nothing
}

Rect::Rect(const Rect& rect)
    : x(rect.x), y(rect.y), width(rect.width), height(rect.height)
{
    // Do nothing
}


#pragma mark - Public 関数

Vector2 Rect::Center() const
{
    return Vector2(x + width / 2, y + height / 2);
}

Vector2 Rect::Max() const
{
    return Vector2(xMax(), yMax());
}

Vector2 Rect::Min() const
{
    return Vector2(xMin(), yMin());
}

Vector2 Rect::Position() const
{
    return Vector2(x, y);
}

void Rect::Set(float _x, float _y, float _width, float _height)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
}

Vector2 Rect::Size() const
{
    return Vector2(width, height);
}

Rect& Rect::operator=(const Rect& rect)
{
    x = rect.x;
    y = rect.y;
    width = rect.width;
    height = rect.height;
    return *this;
}

bool Rect::Contains(const Vector2& pos) const
{
    float theMinX = xMin();
    float theMinY = yMin();
    float theMaxX = xMax();
    float theMaxY = yMax();
    
    return (pos.x >= theMinX && pos.y >= theMinY &&
            pos.x <= theMaxX && pos.y <= theMaxY);
}

bool Rect::Contains(const Vector3& pos) const
{
    float theMinX = xMin();
    float theMinY = yMin();
    float theMaxX = xMax();
    float theMaxY = yMax();

    return (pos.x >= theMinX && pos.y >= theMinY &&
            pos.x <= theMaxX && pos.y <= theMaxY);
}

bool Rect::Contains(const Rect& rect) const
{
    float theMinX = xMin();
    float theMinY = yMin();
    float theMaxX = xMax();
    float theMaxY = yMax();

    float targetMinX = rect.xMin();
    float targetMinY = rect.yMin();
    float targetMaxX = rect.xMax();
    float targetMaxY = rect.yMax();
    
    return (targetMinX >= theMinX && targetMinY >= theMinY &&
            targetMaxX <= theMaxX && targetMaxY <= theMaxY);
}

bool Rect::Overlaps(const Rect& rect) const
{
    float minX1 = xMin();
    float minY1 = yMin();
    float maxX1 = xMax();
    float maxY1 = yMax();

    float minX2 = rect.xMin();
    float minY2 = rect.yMin();
    float maxX2 = rect.xMax();
    float maxY2 = rect.yMax();
    
    return (minX1 < maxX2 && maxX1 > minX2 &&
            minY1 < maxY2 && maxY1 > minY2);
}

float Rect::xMax() const
{
    return std::max(x, x + width);
}

float Rect::yMax() const
{
    return std::max(y, y + height);
}

float Rect::xMin() const
{
    return std::min(x, x + width);
}

float Rect::yMin() const
{
    return std::min(y, y + height);
}

std::string Rect::ToString() const
{
    return ToString("%.1f");
}

std::string Rect::ToString(const std::string& format) const
{
    std::string xStr = FormatString(format.c_str(), x);
    std::string yStr = FormatString(format.c_str(), y);
    std::string widthStr = FormatString(format.c_str(), width);
    std::string heightStr = FormatString(format.c_str(), height);
    return FormatString("(x:%s, y:%s, width:%s, height:%s)", xStr.c_str(), yStr.c_str(), widthStr.c_str(), heightStr.c_str());
}

const char* Rect::c_str() const
{
    return GMObject::c_str();
}

const char* Rect::c_str(const std::string& format) const
{
    return ToString(format).c_str();
}


#pragma mark - 演算子のオーバーロード

bool Rect::operator==(const Rect& rect) const
{
    if (fabsf(x - rect.x) >= 9.99999944E-11f) return false;
    if (fabsf(y - rect.y) >= 9.99999944E-11f) return false;
    if (fabsf(width - rect.width) >= 9.99999944E-11f) return false;
    if (fabsf(height - rect.height) >= 9.99999944E-11f) return false;
    return true;
}

bool Rect::operator!=(const Rect& rect) const
{
    if (fabsf(x - rect.x) >= 9.99999944E-11f) return true;
    if (fabsf(y - rect.y) >= 9.99999944E-11f) return true;
    if (fabsf(width - rect.width) >= 9.99999944E-11f) return true;
    if (fabsf(height - rect.height) >= 9.99999944E-11f) return true;
    return false;
}

Rect Rect::operator+(const Vector2& vec) const
{
    Rect ret(*this);
    ret.x += vec.x;
    ret.y += vec.y;
    return ret;
}

Rect Rect::operator-(const Vector2& vec) const
{
    Rect ret(*this);
    ret.x -= vec.x;
    ret.y -= vec.y;
    return ret;
}

Rect& Rect::operator+=(const Vector2& vec)
{
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Rect& Rect::operator-=(const Vector2& vec)
{
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}


