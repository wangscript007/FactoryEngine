//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Vec3.h"

namespace ftr {

const Mat3x2  Mat3x2::Identity(Mat2::Identity, Vec2(0.0f, 0.0f));

const Vec3 Vec3::X(1.0f, 0.0f, 0.0f);
const Vec3 Vec3::Y(0.0f, 1.0f, 0.0f);
const Vec3 Vec3::Z(0.0f, 0.0f, 1.0f);

Vec3::Vec3(const Vec4& other): mX(other.mX), mY(other.mY), mZ(other.mZ)
{
}

Vec3& Vec3::operator=(const Vec4& other)
{
    mX = other.mX;
    mY = other.mY;
    mZ = other.mZ;

    return *this;
}
    
}


