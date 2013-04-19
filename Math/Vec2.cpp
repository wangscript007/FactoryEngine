//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Vec2.h"

namespace ftr {

Vec2::Vec2(const Vec3& other): mX(other.mX), mY(other.mY)
{
}

Vec2::Vec2(const Vec4& other): mX(other.mX), mY(other.mY)
{
}

Vec2& Vec2::operator=(const Vec3& other)
{
    mX = other.mX;
    mY = other.mY;

    return *this;
}

Vec2& Vec2::operator=(const Vec4& other)
{
    mX = other.mX;
    mY = other.mY;

    return *this;
}

}
