
#pragma once

#include <Math/FTPolygon.h>

class FTRect : public FTPolygon
{
public:
    O5Vec2 m_vOrigin;
    O5Vec2 m_vSize;
    
    FTRect() : m_vOrigin(O5Vec2()), m_vSize(O5Vec2()) {}
    FTRect(const O5Vec2 vOrigin, const O5Vec2 vSize) : m_vOrigin(vOrigin), m_vSize(vSize) {}
    FTRect(const float fX, const float fY, const float fWidth, const float fHeight)
    : m_vOrigin(O5Vec2(fX, fY)), m_vSize(O5Vec2(fWidth, fHeight)) {}
};

