//
// Copyright (c) On5. All rights reserved.
//
#pragma once

class O5Vec2
{
public:
    float       m_fX;
    float       m_fY;

                O5Vec2(): m_fX(0.0f), m_fY(0.0f) {}
                O5Vec2(const O5Vec2& other): m_fX(other.m_fX), m_fY(other.m_fY) {}
    explicit    O5Vec2(const class O5Vec3& other);
    explicit    O5Vec2(const class O5Vec4& other);
                O5Vec2(float fX, float fY): m_fX(fX), m_fY(fY) {}

    O5Vec2      operator-() const {return O5Vec2(-m_fX, -m_fY);}
    float       operator*(const O5Vec2& other) const {return m_fX * other.m_fX + m_fY * other.m_fY;} // Dot product.
    float       operator^(const O5Vec2& other) const {return (m_fX*other.m_fY - m_fY*other.m_fX);} // Cross product.
    O5Vec2      operator-(const O5Vec2& other) const {return O5Vec2(m_fX - other.m_fX, m_fY - other.m_fY);}
    O5Vec2      operator+(const O5Vec2& other) const {return O5Vec2(m_fX + other.m_fX, m_fY + other.m_fY);}
    O5Vec2&     operator=(const O5Vec2& other) {m_fX = other.m_fX; m_fY = other.m_fY; return *this;}
    O5Vec2&     operator=(const class O5Vec3& other);
    O5Vec2&     operator=(const class O5Vec4& other);
    O5Vec2&     operator+=(const O5Vec2& other) {m_fX += other.m_fX; m_fY += other.m_fY; return *this;}
    O5Vec2&     operator-=(const O5Vec2& other) {m_fX -= other.m_fX; m_fY -= other.m_fY; return *this;}
    O5Vec2&     operator*=(float value) {m_fX *= value; m_fY *= value; return *this;}
    O5Vec2      operator*(float value) const {return O5Vec2(m_fX * value, m_fY * value);}
    O5Vec2      operator/(float value) const {return O5Vec2(m_fX / value, m_fY / value);}
    O5Vec2&     operator/=(float value) {m_fX /= value; m_fY /= value; return *this;}
    O5Vec2&     operator*=(const class O5Mat2& matrix);
    float       operator[](int index) const {return (&m_fX)[index];}
    float&      operator[](int index) {return (&m_fX)[index];}
    bool        operator==(const O5Vec2& other) const {return O5Approximately(m_fX, other.m_fX) && O5Approximately(m_fY, other.m_fY);}
    bool        operator!=(const O5Vec2& other) const {return !O5Approximately(m_fX, other.m_fX) || !O5Approximately(m_fY, other.m_fY);}

    void        Set(float fX, float fY) {m_fX = fX; m_fY = fY;}
    float       Distance(const O5Vec2& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(m_fX * m_fX + m_fY * m_fY);}
    O5Vec2      Lerp(const O5Vec2& vB, float fT) const {return O5Vec2(O5Lerp(m_fX, vB.m_fX, fT), O5Lerp(m_fY, vB.m_fY, fT));}
    O5Vec2      Bezier(const O5Vec2& vB, const O5Vec2& vC, const O5Vec2& vD, float fT) const;
    O5Vec2      Maximum(const O5Vec2& other) const {return O5Vec2(O5Maximum(m_fX, other.m_fX), O5Maximum(m_fY, other.m_fY));}
    O5Vec2      Minimum(const O5Vec2& other) const {return O5Vec2(O5Minimum(m_fX, other.m_fX), O5Minimum(m_fY, other.m_fY));}
    float       Normalize();
    void        Zero() {m_fX = 0.0f; m_fY = 0.0f;}
};

inline O5Vec2 O5Vec2::Bezier(const O5Vec2& vB, const O5Vec2& vC, const O5Vec2& vD, float fT) const
{
    return O5Vec2(O5Bezier(m_fX, vB.m_fX, vC.m_fX, vD.m_fX, fT), O5Bezier(m_fY, vB.m_fY, vC.m_fY, vD.m_fY, fT));
}

inline float O5Vec2::Normalize()
{
    float length = Length();
    if(length > 0.0f)
    {
        m_fX /= length;
        m_fY /= length;
    }
    return length;
}
