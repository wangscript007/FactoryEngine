
#pragma once

#include <Math/Polygon.h>

namespace Factory {

class Rect : public Polygon
{
public:
    O5Vec2 m_vOrigin;
    O5Vec2 m_vSize;
    
    Rect() : m_vOrigin(O5Vec2()), m_vSize(O5Vec2()) {}
    Rect(const O5Vec2 vOrigin, const O5Vec2 vSize) : m_vOrigin(vOrigin), m_vSize(vSize) {}
    Rect(const float fX, const float fY, const float fWidth, const float fHeight)
    : m_vOrigin(O5Vec2(fX, fY)), m_vSize(O5Vec2(fWidth, fHeight)) {}
};

}