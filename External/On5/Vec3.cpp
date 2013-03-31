//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Vec3.h"

const O5Mat3x2  O5Mat3x2::Identity(O5Mat2::Identity, O5Vec2(0.0f, 0.0f));

const O5Vec3 O5Vec3::X(1.0f, 0.0f, 0.0f);
const O5Vec3 O5Vec3::Y(0.0f, 1.0f, 0.0f);
const O5Vec3 O5Vec3::Z(0.0f, 0.0f, 1.0f);

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


