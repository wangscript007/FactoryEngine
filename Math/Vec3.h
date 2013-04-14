//
// Copyright (c) On5. All rights reserved.
//

#pragma once

class O5Vec3
{
public:
    static const O5Vec3 X;
    static const O5Vec3 Y;
    static const O5Vec3 Z;
    
    float   m_fX;
    float   m_fY;
    float   m_fZ;

                O5Vec3(): m_fX(0.0f), m_fY(0.0f), m_fZ(0.0f) {}
                O5Vec3(const O5Vec3& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(other.m_fZ) {}
    explicit    O5Vec3(const O5Vec2& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(0.0f) {}
    explicit    O5Vec3(const class O5Vec4& other);
                O5Vec3(float fX, float fY, float fZ): m_fX(fX), m_fY(fY), m_fZ(fZ) {}

    O5Vec3      operator-() const {return O5Vec3(-m_fX, -m_fY, -m_fZ);}
    float       operator*(const O5Vec3& other) const {return m_fX * other.m_fX + m_fY * other.m_fY + m_fZ * other.m_fZ;} // Dot product.
    O5Vec3      operator^(const O5Vec3& other) const; // Cross product.
    O5Vec3      operator-(const O5Vec3& other) const {return O5Vec3(m_fX - other.m_fX, m_fY - other.m_fY, m_fZ - other.m_fZ);}
    O5Vec3      operator+(const O5Vec3& other) const {return O5Vec3(m_fX + other.m_fX, m_fY + other.m_fY, m_fZ + other.m_fZ);}
    O5Vec3&     operator=(const O5Vec3& other) {m_fX = other.m_fX; m_fY = other.m_fY; m_fZ = other.m_fZ; return *this;}
    O5Vec3&     operator=(const O5Vec2& other) {m_fX = other.m_fX; m_fY = other.m_fY; m_fZ = 0.0f; return *this;}
    O5Vec3&     operator=(const class O5Vec4& other);
    O5Vec3&     operator+=(const O5Vec3& other) {m_fX += other.m_fX; m_fY += other.m_fY; m_fZ += other.m_fZ; return *this;}
    O5Vec3&     operator-=(const O5Vec3& other) {m_fX -= other.m_fX; m_fY -= other.m_fY; m_fZ -= other.m_fZ; return *this;}
    O5Vec3&     operator*=(float value) {m_fX *= value; m_fY *= value; m_fZ *= value; return *this;}
    O5Vec3      operator*(float value) const {return O5Vec3(m_fX * value, m_fY * value, m_fZ * value);}
    O5Vec3&     operator/=(float value) {m_fX /= value; m_fY /= value; m_fZ /= value; return *this;}
    O5Vec3      operator/(float value) const {return O5Vec3(m_fX / value, m_fY / value, m_fZ / value);}
    O5Vec3&     operator*=(const class O5Mat4& matrix);
    float       operator[](int index) const {return (&m_fX)[index];}
    float&      operator[](int index) {return (&m_fX)[index];}
    bool        operator==(const O5Vec3& other) const {return O5Approximately(m_fX, other.m_fX) && O5Approximately(m_fY, other.m_fY) && O5Approximately(m_fZ, other.m_fZ);}
    bool        operator!=(const O5Vec3& other) const {return !O5Approximately(m_fX, other.m_fX) || !O5Approximately(m_fY, other.m_fY) || !O5Approximately(m_fZ, other.m_fZ);}

    void        Set(float fX, float fY, float fZ) {m_fX = fX; m_fY = fY; m_fZ = fZ;}
    float       Distance(const O5Vec3& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ);}
    float       Angle(const O5Vec3& other) const { return acosf(*this * other) / (Length() + other.Length()); }
    float       ProjectionIn(const O5Vec3& other) { return Length() * cosf(Angle(other)); }
    O5Vec3      Bezier(const O5Vec3& vB, const O5Vec3& vC, const O5Vec3& vD, float fT) const;
    O5Vec3      Lerp(const O5Vec3& vB, float fT) const {return O5Vec3(O5Lerp(m_fX, vB.m_fX, fT), O5Lerp(m_fY, vB.m_fY, fT), O5Lerp(m_fZ, vB.m_fZ, fT));}
    float       Normalize();
    void        Zero() {m_fX = 0.0f; m_fY = 0.0f; m_fZ = 0.0f;}
    float       Max() const;
    float       Min() const;
    
};

inline float O5Vec3::Max() const
{
    float fMax = (*this)[0];
    for(int i = 1; i < 3; i++) {
        if ((*this)[i] > fMax) {
            fMax = (*this)[i];
        }
    }
    return fMax;
}

inline float O5Vec3::Min() const
{
    float fMin = (*this)[0];
    for(int i = 1; i < 3; i++) {
        if ((*this)[i] > fMin) {
            fMin = (*this)[i];
        }
    }
    return fMin;
}


inline O5Vec3 O5Vec3::Bezier(const O5Vec3& vB, const O5Vec3& vC, const O5Vec3& vD, float fT) const
{
    return O5Vec3(O5Bezier(m_fX, vB.m_fX, vC.m_fX, vD.m_fX, fT), O5Bezier(m_fY, vB.m_fY, vC.m_fY, vD.m_fY, fT), O5Bezier(m_fZ, vB.m_fZ, vC.m_fZ, vD.m_fZ, fT));
}

inline O5Vec3 O5Vec3::operator^(const O5Vec3& other) const
{
    float fX = m_fY * other.m_fZ - m_fZ * other.m_fY;
    float fY = m_fZ * other.m_fX - m_fX * other.m_fZ;
    float fZ = m_fX * other.m_fY - m_fY * other.m_fX;

    return O5Vec3(fX, fY, fZ);
}

inline float O5Vec3::Normalize()
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
