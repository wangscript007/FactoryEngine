//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Vec3.h"

namespace Factory {

const Mat3x2  Mat3x2::Identity(Mat2::Identity, Vec2(0.0f, 0.0f));

const Vec3 Vec3::X(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::Y(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::Z(0.0f, 0.0f, 1.0f);

Vec3::Vec3(const Vec4& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(other.m_fZ)
{
}

Vec3& Vec3::operator=(const Vec4& other)
{
    m_fX = other.m_fX;
    m_fY = other.m_fY;
    m_fZ = other.m_fZ;

    return *this;
}
    
}


