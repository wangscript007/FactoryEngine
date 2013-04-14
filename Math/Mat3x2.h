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

    Mat2                  m_vX;
    Vec2                  m_vW;

                            Mat3x2() {}
                            Mat3x2(const Mat3x2& other): m_vX(other.m_vX), m_vW(other.m_vW) {}
                            Mat3x2(const Mat2& vX, const Vec2& vW): m_vX(vX), m_vW(vW) {}

    Mat3x2&               operator=(const Mat3x2& other) {m_vX = other.m_vX; m_vW = other.m_vW; return *this;}
    const Vec2&           operator[](int index) const {return (&m_vX.m_vX)[index];}
    Vec2&                 operator[](int index) {return (&m_vX.m_vX)[index];}
    bool                    operator==(const Mat3x2& other) const {return m_vX == other.m_vX && m_vW == other.m_vW;}
    bool                    operator!=(const Mat3x2& other) const {return m_vX != other.m_vX || m_vW != other.m_vW;}

    void                    Set(const Mat2& vX, const Vec2& vW) {m_vX = vX; m_vW = vW;}
};

}
