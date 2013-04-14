//
// Copyright (c) On5. All rights reserved.
//
#pragma once

namespace Factory {

class Vec2
{
public:
    float       m_fX;
    float       m_fY;

                Vec2(): m_fX(0.0f), m_fY(0.0f) {}
                Vec2(const Vec2& other): m_fX(other.m_fX), m_fY(other.m_fY) {}
    explicit    Vec2(const class Vec3& other);
    explicit    Vec2(const class Vec4& other);
                Vec2(float fX, float fY): m_fX(fX), m_fY(fY) {}

    Vec2        operator-() const {return Vec2(-m_fX, -m_fY);}
    float       operator*(const Vec2& other) const {return m_fX * other.m_fX + m_fY * other.m_fY;} // Dot product.
    float       operator^(const Vec2& other) const {return (m_fX*other.m_fY - m_fY*other.m_fX);} // Cross product.
    Vec2        operator-(const Vec2& other) const {return Vec2(m_fX - other.m_fX, m_fY - other.m_fY);}
    Vec2        operator+(const Vec2& other) const {return Vec2(m_fX + other.m_fX, m_fY + other.m_fY);}
    Vec2&       operator=(const Vec2& other) {m_fX = other.m_fX; m_fY = other.m_fY; return *this;}
    Vec2&       operator=(const class Vec3& other);
    Vec2&       operator=(const class Vec4& other);
    Vec2&       operator+=(const Vec2& other) {m_fX += other.m_fX; m_fY += other.m_fY; return *this;}
    Vec2&       operator-=(const Vec2& other) {m_fX -= other.m_fX; m_fY -= other.m_fY; return *this;}
    Vec2&       operator*=(float value) {m_fX *= value; m_fY *= value; return *this;}
    Vec2        operator*(float value) const {return Vec2(m_fX * value, m_fY * value);}
    Vec2        operator/(float value) const {return Vec2(m_fX / value, m_fY / value);}
    Vec2&       operator/=(float value) {m_fX /= value; m_fY /= value; return *this;}
    Vec2&       operator*=(const class Mat2& matrix);
    float       operator[](int index) const {return (&m_fX)[index];}
    float&      operator[](int index) {return (&m_fX)[index];}
    bool        operator==(const Vec2& other) const {return Util::Approximately(m_fX, other.m_fX) && Util::Approximately(m_fY, other.m_fY);}
    bool        operator!=(const Vec2& other) const {return !Util::Approximately(m_fX, other.m_fX) || !Util::Approximately(m_fY, other.m_fY);}

    void        Set(float fX, float fY) {m_fX = fX; m_fY = fY;}
    float       Distance(const Vec2& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(m_fX * m_fX + m_fY * m_fY);}
    Vec2        Lerp(const Vec2& vB, float fT) const {return Vec2(Util::Lerp(m_fX, vB.m_fX, fT), Util::Lerp(m_fY, vB.m_fY, fT));}
    Vec2        Bezier(const Vec2& vB, const Vec2& vC, const Vec2& vD, float fT) const;
    Vec2        Maximum(const Vec2& other) const {return Vec2(Util::Maximum(m_fX, other.m_fX), Util::Maximum(m_fY, other.m_fY));}
    Vec2        Minimum(const Vec2& other) const {return Vec2(Util::Minimum(m_fX, other.m_fX), Util::Minimum(m_fY, other.m_fY));}
    float       Normalize();
    void        Zero() {m_fX = 0.0f; m_fY = 0.0f;}
};

inline Vec2 Vec2::Bezier(const Vec2& vB, const Vec2& vC, const Vec2& vD, float fT) const
{
    return Vec2(Util::Bezier(m_fX, vB.m_fX, vC.m_fX, vD.m_fX, fT), Util::Bezier(m_fY, vB.m_fY, vC.m_fY, vD.m_fY, fT));
}

inline float Vec2::Normalize()
{
    float length = Length();
    if(length > 0.0f)
    {
        m_fX /= length;
        m_fY /= length;
    }
    return length;
}

}