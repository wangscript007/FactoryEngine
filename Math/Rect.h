
#pragma once

#include <Math/Polygon.h>

namespace ftr {

class Rect : public Polygon
{
public:
    Vec2 mOrigin;
    Vec2 mSize;
    
    Rect() : mOrigin(Vec2()), mSize(Vec2()) {}
    Rect(const Vec2 origin, const Vec2 size) : mOrigin(origin), mSize(size) {}
    Rect(const float x, const float y, const float width, const float fHeight)
    : mOrigin(Vec2(x, y)), mSize(Vec2(width, fHeight)) {}
};

}