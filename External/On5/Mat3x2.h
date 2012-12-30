//
// Copyright (c) On5. All rights reserved.
//
#pragma once

class O5_ALIGN(16) O5Mat3x2
{
public:
    static const O5Mat3x2   Zero;
    static const O5Mat3x2   Identity;

    O5Mat2                  m_vX;
    O5Vec2                  m_vW;

                            O5Mat3x2() {}
                            O5Mat3x2(const O5Mat3x2& other): m_vX(other.m_vX), m_vW(other.m_vW) {}
                            O5Mat3x2(const O5Mat2& vX, const O5Vec2& vW): m_vX(vX), m_vW(vW) {}

    O5Mat3x2&               operator=(const O5Mat3x2& other) {m_vX = other.m_vX; m_vW = other.m_vW; return *this;}
    const O5Vec2&           operator[](int index) const {return (&m_vX.m_vX)[index];}
    O5Vec2&                 operator[](int index) {return (&m_vX.m_vX)[index];}
    bool                    operator==(const O5Mat3x2& other) const {return m_vX == other.m_vX && m_vW == other.m_vW;}
    bool                    operator!=(const O5Mat3x2& other) const {return m_vX != other.m_vX || m_vW != other.m_vW;}

    void                    Set(const O5Mat2& vX, const O5Vec2& vW) {m_vX = vX; m_vW = vW;}
};
