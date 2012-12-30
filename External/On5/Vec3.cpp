//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Vec3.h"

O5Vec3::O5Vec3(const O5Vec4& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(other.m_fZ)
{
}

O5Vec3& O5Vec3::operator=(const O5Vec4& other)
{
    m_fX = other.m_fX;
    m_fY = other.m_fY;
    m_fZ = other.m_fZ;

    return *this;
}
