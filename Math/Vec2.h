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
                Vec2(float x, float y): mX(x), mY(y) {}

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

    void        set(float x, float y) {mX = x; mY = y;}
    float       Distance(const Vec2& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(mX * mX + mY * mY);}
    Vec2        Lerp(const Vec2& b, float fT) const {return Vec2(Util::Lerp(mX, b.mX, fT), Util::Lerp(mY, b.mY, fT));}
    Vec2        Bezier(const Vec2& b, const Vec2& vC, const Vec2& vD, float fT) const;
    Vec2        Maximum(const Vec2& other) const {return Vec2(Util::Maximum(mX, other.mX), Util::Maximum(mY, other.mY));}
    Vec2        Minimum(const Vec2& other) const {return Vec2(Util::Minimum(mX, other.mX), Util::Minimum(mY, other.mY));}
    float       Normalize();
    void        Zero() {mX = 0.0f; mY = 0.0f;}
};

inline Vec2 Vec2::Bezier(const Vec2& b, const Vec2& vC, const Vec2& vD, float fT) const
{
    return Vec2(Util::Bezier(mX, b.mX, vC.mX, vD.mX, fT), Util::Bezier(mY, b.mY, vC.mY, vD.mY, fT));
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