//
// Copyright (c) On5. All rights reserved.
//
#pragma once

namespace ftr {

class Vec2
{
public:
    float       mX;
    float       mY;

                Vec2(): mX(0.0f), mY(0.0f) {}
                Vec2(const Vec2& other): mX(other.mX), mY(other.mY) {}
    explicit    Vec2(const class Vec3& other);
    explicit    Vec2(const class Vec4& other);
                Vec2(float fX, float fY): mX(fX), mY(fY) {}

    Vec2        operator-() const {return Vec2(-mX, -mY);}
    float       operator*(const Vec2& other) const {return mX * other.mX + mY * other.mY;} // Dot product.
    float       operator^(const Vec2& other) const {return (mX*other.mY - mY*other.mX);} // Cross product.
    Vec2        operator-(const Vec2& other) const {return Vec2(mX - other.mX, mY - other.mY);}
    Vec2        operator+(const Vec2& other) const {return Vec2(mX + other.mX, mY + other.mY);}
    Vec2&       operator=(const Vec2& other) {mX = other.mX; mY = other.mY; return *this;}
    Vec2&       operator=(const class Vec3& other);
    Vec2&       operator=(const class Vec4& other);
    Vec2&       operator+=(const Vec2& other) {mX += other.mX; mY += other.mY; return *this;}
    Vec2&       operator-=(const Vec2& other) {mX -= other.mX; mY -= other.mY; return *this;}
    Vec2&       operator*=(float value) {mX *= value; mY *= value; return *this;}
    Vec2        operator*(float value) const {return Vec2(mX * value, mY * value);}
    Vec2        operator/(float value) const {return Vec2(mX / value, mY / value);}
    Vec2&       operator/=(float value) {mX /= value; mY /= value; return *this;}
    Vec2&       operator*=(const class Mat2& matrix);
    float       operator[](int index) const {return (&mX)[index];}
    float&      operator[](int index) {return (&mX)[index];}
    bool        operator==(const Vec2& other) const {return Util::Approximately(mX, other.mX) && Util::Approximately(mY, other.mY);}
    bool        operator!=(const Vec2& other) const {return !Util::Approximately(mX, other.mX) || !Util::Approximately(mY, other.mY);}

    void        Set(float fX, float fY) {mX = fX; mY = fY;}
    float       Distance(const Vec2& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(mX * mX + mY * mY);}
    Vec2        Lerp(const Vec2& vB, float fT) const {return Vec2(Util::Lerp(mX, vB.mX, fT), Util::Lerp(mY, vB.mY, fT));}
    Vec2        Bezier(const Vec2& vB, const Vec2& vC, const Vec2& vD, float fT) const;
    Vec2        Maximum(const Vec2& other) const {return Vec2(Util::Maximum(mX, other.mX), Util::Maximum(mY, other.mY));}
    Vec2        Minimum(const Vec2& other) const {return Vec2(Util::Minimum(mX, other.mX), Util::Minimum(mY, other.mY));}
    float       Normalize();
    void        Zero() {mX = 0.0f; mY = 0.0f;}
};

inline Vec2 Vec2::Bezier(const Vec2& vB, const Vec2& vC, const Vec2& vD, float fT) const
{
    return Vec2(Util::Bezier(mX, vB.mX, vC.mX, vD.mX, fT), Util::Bezier(mY, vB.mY, vC.mY, vD.mY, fT));
}

inline float Vec2::Normalize()
{
    float length = Length();
    if(length > 0.0f)
    {
        mX /= length;
        mY /= length;
    }
    return length;
}

}