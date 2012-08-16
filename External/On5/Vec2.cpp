//
// Copyright (c) 2012 On5. All rights reserved.
//

#include <FactoryEngine.h>

O5Vec2::O5Vec2(const O5Vec3& other): m_fX(other.m_fX), m_fY(other.m_fY)
{
}

O5Vec2::O5Vec2(const O5Vec4& other): m_fX(other.m_fX), m_fY(other.m_fY)
{
}

O5Vec2& O5Vec2::operator=(const O5Vec3& other)
{
    m_fX = other.m_fX;
    m_fY = other.m_fY;

    return *this;
}

O5Vec2& O5Vec2::operator=(const O5Vec4& other)
{
    m_fX = other.m_fX;
    m_fY = other.m_fY;

    return *this;
}
