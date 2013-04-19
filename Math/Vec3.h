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
    
    float   mX;
    float   mY;
    float   mZ;

                Vec3(): mX(0.0f), mY(0.0f), mZ(0.0f) {}
                Vec3(const Vec3& other): mX(other.mX), mY(other.mY), mZ(other.mZ) {}
    explicit    Vec3(const Vec2& other): mX(other.mX), mY(other.mY), mZ(0.0f) {}
    explicit    Vec3(const class Vec4& other);
                Vec3(float fX, float fY, float fZ): mX(fX), mY(fY), mZ(fZ) {}

    Vec3      operator-() const {return Vec3(-mX, -mY, -mZ);}
    float       operator*(const Vec3& other) const {return mX * other.mX + mY * other.mY + mZ * other.mZ;} // Dot product.
    Vec3      operator^(const Vec3& other) const; // Cross product.
    Vec3      operator-(const Vec3& other) const {return Vec3(mX - other.mX, mY - other.mY, mZ - other.mZ);}
    Vec3      operator+(const Vec3& other) const {return Vec3(mX + other.mX, mY + other.mY, mZ + other.mZ);}
    Vec3&     operator=(const Vec3& other) {mX = other.mX; mY = other.mY; mZ = other.mZ; return *this;}
    Vec3&     operator=(const Vec2& other) {mX = other.mX; mY = other.mY; mZ = 0.0f; return *this;}
    Vec3&     operator=(const class Vec4& other);
    Vec3&     operator+=(const Vec3& other) {mX += other.mX; mY += other.mY; mZ += other.mZ; return *this;}
    Vec3&     operator-=(const Vec3& other) {mX -= other.mX; mY -= other.mY; mZ -= other.mZ; return *this;}
    Vec3&     operator*=(float value) {mX *= value; mY *= value; mZ *= value; return *this;}
    Vec3      operator*(float value) const {return Vec3(mX * value, mY * value, mZ * value);}
    Vec3&     operator/=(float value) {mX /= value; mY /= value; mZ /= value; return *this;}
    Vec3      operator/(float value) const {return Vec3(mX / value, mY / value, mZ / value);}
    Vec3&     operator*=(const class Mat4& matrix);
    float       operator[](int index) const {return (&mX)[index];}
    float&      operator[](int index) {return (&mX)[index];}
    bool        operator==(const Vec3& other) const {return Util::Approximately(mX, other.mX) && Util::Approximately(mY, other.mY) && Util::Approximately(mZ, other.mZ);}
    bool        operator!=(const Vec3& other) const {return !Util::Approximately(mX, other.mX) || !Util::Approximately(mY, other.mY) || !Util::Approximately(mZ, other.mZ);}

    void        Set(float fX, float fY, float fZ) {mX = fX; mY = fY; mZ = fZ;}
    float       Distance(const Vec3& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(mX * mX + mY * mY + mZ * mZ);}
    float       Angle(const Vec3& other) const { return acosf(*this * other) / (Length() + other.Length()); }
    float       ProjectionIn(const Vec3& other) { return Length() * cosf(Angle(other)); }
    Vec3      Bezier(const Vec3& vB, const Vec3& vC, const Vec3& vD, float fT) const;
    Vec3      Lerp(const Vec3& vB, float fT) const {return Vec3(Util::Lerp(mX, vB.mX, fT), Util::Lerp(mY, vB.mY, fT), Util::Lerp(mZ, vB.mZ, fT));}
    float       Normalize();
    void        Zero() {mX = 0.0f; mY = 0.0f; mZ = 0.0f;}
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
    return Vec3(Util::Bezier(mX, vB.mX, vC.mX, vD.mX, fT), Util::Bezier(mY, vB.mY, vC.mY, vD.mY, fT), Util::Bezier(mZ, vB.mZ, vC.mZ, vD.mZ, fT));
}

inline Vec3 Vec3::operator^(const Vec3& other) const
{
    float fX = mY * other.mZ - mZ * other.mY;
    float fY = mZ * other.mX - mX * other.mZ;
    float fZ = mX * other.mY - mY * other.mX;

    return Vec3(fX, fY, fZ);
}

inline float Vec3::Normalize()
{
    float length = Length();

    if(length > 0.0f)
    {
        mX /= length;
        mY /= length;
        mZ /= length;
    }

    return length;
}

}