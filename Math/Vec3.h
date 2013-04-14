//
// Copyright (c) On5. All rights reserved.
//

#pragma once

namespace ftr {

class Vec3
{
public:
    static const Vec3 X;
    static const Vec3 Y;
    static const Vec3 Z;
    
    float   m_fX;
    float   m_fY;
    float   m_fZ;

                Vec3(): m_fX(0.0f), m_fY(0.0f), m_fZ(0.0f) {}
                Vec3(const Vec3& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(other.m_fZ) {}
    explicit    Vec3(const Vec2& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(0.0f) {}
    explicit    Vec3(const class Vec4& other);
                Vec3(float fX, float fY, float fZ): m_fX(fX), m_fY(fY), m_fZ(fZ) {}

    Vec3      operator-() const {return Vec3(-m_fX, -m_fY, -m_fZ);}
    float       operator*(const Vec3& other) const {return m_fX * other.m_fX + m_fY * other.m_fY + m_fZ * other.m_fZ;} // Dot product.
    Vec3      operator^(const Vec3& other) const; // Cross product.
    Vec3      operator-(const Vec3& other) const {return Vec3(m_fX - other.m_fX, m_fY - other.m_fY, m_fZ - other.m_fZ);}
    Vec3      operator+(const Vec3& other) const {return Vec3(m_fX + other.m_fX, m_fY + other.m_fY, m_fZ + other.m_fZ);}
    Vec3&     operator=(const Vec3& other) {m_fX = other.m_fX; m_fY = other.m_fY; m_fZ = other.m_fZ; return *this;}
    Vec3&     operator=(const Vec2& other) {m_fX = other.m_fX; m_fY = other.m_fY; m_fZ = 0.0f; return *this;}
    Vec3&     operator=(const class Vec4& other);
    Vec3&     operator+=(const Vec3& other) {m_fX += other.m_fX; m_fY += other.m_fY; m_fZ += other.m_fZ; return *this;}
    Vec3&     operator-=(const Vec3& other) {m_fX -= other.m_fX; m_fY -= other.m_fY; m_fZ -= other.m_fZ; return *this;}
    Vec3&     operator*=(float value) {m_fX *= value; m_fY *= value; m_fZ *= value; return *this;}
    Vec3      operator*(float value) const {return Vec3(m_fX * value, m_fY * value, m_fZ * value);}
    Vec3&     operator/=(float value) {m_fX /= value; m_fY /= value; m_fZ /= value; return *this;}
    Vec3      operator/(float value) const {return Vec3(m_fX / value, m_fY / value, m_fZ / value);}
    Vec3&     operator*=(const class Mat4& matrix);
    float       operator[](int index) const {return (&m_fX)[index];}
    float&      operator[](int index) {return (&m_fX)[index];}
    bool        operator==(const Vec3& other) const {return Util::Approximately(m_fX, other.m_fX) && Util::Approximately(m_fY, other.m_fY) && Util::Approximately(m_fZ, other.m_fZ);}
    bool        operator!=(const Vec3& other) const {return !Util::Approximately(m_fX, other.m_fX) || !Util::Approximately(m_fY, other.m_fY) || !Util::Approximately(m_fZ, other.m_fZ);}

    void        Set(float fX, float fY, float fZ) {m_fX = fX; m_fY = fY; m_fZ = fZ;}
    float       Distance(const Vec3& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);}
    float       Angle(const Vec3& other) const { return acosf(*this * other) / (Length() + other.Length()); }
    float       ProjectionIn(const Vec3& other) { return Length() * cosf(Angle(other)); }
    Vec3      Bezier(const Vec3& vB, const Vec3& vC, const Vec3& vD, float fT) const;
    Vec3      Lerp(const Vec3& vB, float fT) const {return Vec3(Util::Lerp(m_fX, vB.m_fX, fT), Util::Lerp(m_fY, vB.m_fY, fT), Util::Lerp(m_fZ, vB.m_fZ, fT));}
    float       Normalize();
    void        Zero() {m_fX = 0.0f; m_fY = 0.0f; m_fZ = 0.0f;}
    float       Max() const;
    float       Min() const;
    
};

inline float Vec3::Max() const
{
    float fMax = (*this)[0];
    for(int i = 1; i < 3; i++) {
        if ((*this)[i] > fMax) {
            fMax = (*this)[i];
        }
    }
    return fMax;
}

inline float Vec3::Min() const
{
    float fMin = (*this)[0];
    for(int i = 1; i < 3; i++) {
        if ((*this)[i] > fMin) {
            fMin = (*this)[i];
        }
    }
    return fMin;
}


inline Vec3 Vec3::Bezier(const Vec3& vB, const Vec3& vC, const Vec3& vD, float fT) const
{
    return Vec3(Util::Bezier(m_fX, vB.m_fX, vC.m_fX, vD.m_fX, fT), Util::Bezier(m_fY, vB.m_fY, vC.m_fY, vD.m_fY, fT), Util::Bezier(m_fZ, vB.m_fZ, vC.m_fZ, vD.m_fZ, fT));
}

inline Vec3 Vec3::operator^(const Vec3& other) const
{
    float fX = m_fY * other.m_fZ - m_fZ * other.m_fY;
    float fY = m_fZ * other.m_fX - m_fX * other.m_fZ;
    float fZ = m_fX * other.m_fY - m_fY * other.m_fX;

    return Vec3(fX, fY, fZ);
}

inline float Vec3::Normalize()
{
    float length = Length();

    if(length > 0.0f)
    {
        m_fX /= length;
        m_fY /= length;
        m_fZ /= length;
    }

    return length;
}

}