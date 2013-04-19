//
// Copyright (c) On5. All rights reserved.
//
#pragma once

namespace ftr {

class _ALIGN(16) Mat3x2
{
public:
    static const Mat3x2   Zero;
    static const Mat3x2   Identity;

    Mat2                  mX;
    Vec2                  mW;

                            Mat3x2() {}
                            Mat3x2(const Mat3x2& other): mX(other.mX), mW(other.mW) {}
                            Mat3x2(const Mat2& vX, const Vec2& vW): mX(vX), mW(vW) {}

    Mat3x2&               operator=(const Mat3x2& other) {mX = other.mX; mW = other.mW; return *this;}
    const Vec2&           operator[](int index) const {return (&mX.mX)[index];}
    Vec2&                 operator[](int index) {return (&mX.mX)[index];}
    bool                    operator==(const Mat3x2& other) const {return mX == other.mX && mW == other.mW;}
    bool                    operator!=(const Mat3x2& other) const {return mX != other.mX || mW != other.mW;}

    void                    set(const Mat2& vX, const Vec2& vW) {mX = vX; mW = vW;}
};

}
