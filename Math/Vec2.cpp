//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Vec2.h"

namespace Factory {

Vec2::Vec2(const Vec3& other): m_fX(other.m_fX), m_fY(other.m_fY)
{
}

Vec2::Vec2(const Vec4& other): m_fX(other.m_fX), m_fY(other.m_fY)
{
}

Vec2& Vec2::operator=(const Vec3& other)
{
    m_fX = other.m_fX;
    m_fY = other.m_fY;

    return *this;
}

Vec2& Vec2::operator=(const Vec4& other)
{
    m_fX = other.m_fX;
    m_fY = other.m_fY;

    return *this;
}

}
