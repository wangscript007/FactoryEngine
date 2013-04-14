//
// Copyright (c) On5. All rights reserved.
//

#pragma once

namespace Factory {

class _ALIGN(16) Vec4
{
public:
    float       m_fX;
    float       m_fY;
    float       m_fZ;
    float       m_fW;

                Vec4(): m_fX(0.0f), m_fY(0.0f), m_fZ(0.0f), m_fW(0.0f) {}
                Vec4(const Vec4& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(other.m_fZ), m_fW(other.m_fW) {}
    explicit    Vec4(const Vec2& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(0.0f), m_fW(0.0f) {}
    explicit    Vec4(const Vec3& other): m_fX(other.m_fX), m_fY(other.m_fY), m_fZ(other.m_fZ), m_fW(0.0f) {}
                Vec4(float fX, float fY, float fZ, float fW): m_fX(fX), m_fY(fY), m_fZ(fZ), m_fW(fW) {}

    Vec4      operator-() const {return Vec4(-m_fX, -m_fY, -m_fZ, -m_fW);}
    float       operator*(const Vec4& other) const {return m_fX * other.m_fX + m_fY * other.m_fY + m_fZ * other.m_fZ + m_fW * other.m_fW;} // Dot product.
    Vec4      operator-(const Vec4& other) const {return Vec4(m_fX - other.m_fX, m_fY - other.m_fY, m_fZ - other.m_fZ, m_fW - other.m_fW);}
    Vec4      operator+(const Vec4& other) const {return Vec4(m_fX + other.m_fX, m_fY + other.m_fY, m_fZ + other.m_fZ, m_fW + other.m_fW);}
    Vec4&     operator=(const Vec4& other) {m_fX = other.m_fX; m_fY = other.m_fY; m_fZ = other.m_fZ; m_fW = other.m_fW; return *this;}
    Vec4&     operator=(const Vec3& other) {m_fX = other.m_fX; m_fY = other.m_fY; m_fZ = other.m_fZ; m_fW = 0.0f; return *this;}
    Vec4&     operator=(const Vec2& other) {m_fX = other.m_fX; m_fY = other.m_fY; m_fZ = 0.0f; m_fW = 0.0f; return *this;}
    Vec4&     operator+=(const Vec4& other) {m_fX += other.m_fX; m_fY += other.m_fY; m_fZ += other.m_fZ; m_fW += other.m_fW; return *this;}
    Vec4&     operator-=(const Vec4& other) {m_fX -= other.m_fX; m_fY -= other.m_fY; m_fZ -= other.m_fZ; m_fW -= other.m_fW; return *this;}
    Vec4&     operator*=(float value) {m_fX *= value; m_fY *= value; m_fZ *= value; m_fW *= value; return *this;}
    Vec4      operator*(float value) const {return Vec4(m_fX * value, m_fY * value, m_fZ * value, m_fW * value);}
    Vec4&     operator/=(float value) {m_fX /= value; m_fY /= value; m_fZ /= value; m_fW /= value; return *this;}
    Vec4      operator/(float value) const {return Vec4(m_fX / value, m_fY / value, m_fZ / value, m_fW / value);}
    Vec4&     operator*=(const class Mat4& matrix);
    float       operator[](int index) const {return (&m_fX)[index];}
    float&      operator[](int index) {return (&m_fX)[index];}
    bool        operator==(const Vec4& other) const {return Util::Approximately(m_fX, other.m_fX) && Util::Approximately(m_fY, other.m_fY) && Util::Approximately(m_fZ, other.m_fZ) && Util::Approximately(m_fW, other.m_fW);}
    bool        operator!=(const Vec4& other) const {return !Util::Approximately(m_fX, other.m_fX) || !Util::Approximately(m_fY, other.m_fY) || !Util::Approximately(m_fZ, other.m_fZ) || !Util::Approximately(m_fW, other.m_fW);}

    void        Set(float fX, float fY, float fZ, float fW) {m_fX = fX; m_fY = fY; m_fZ = fZ; m_fW = fW;}
    float       Distance(const Vec4& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(m_fX * m_fX + m_fY * m_fY + m_fZ * m_fZ + m_fW * m_fW);}
    float       Normalize();
    void        Zero() {m_fX = 0.0f; m_fY = 0.0f; m_fZ = 0.0f; m_fW = 0.0f;}
};

inline float Vec4::Normalize()
{
    float length = Length();

    if(length > 0.0f)
    {
        m_fX /= length;
        m_fY /= length;
        m_fZ /= length;
        m_fW /= length;
    }

    return length;
}

}