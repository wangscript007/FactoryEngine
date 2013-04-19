//
// Copyright (c) On5. All rights reserved.
//

#pragma once

namespace ftr {

class _ALIGN(16) Vec4
{
public:
    float       mX;
    float       mY;
    float       mZ;
    float       mW;

                Vec4(): mX(0.0f), mY(0.0f), mZ(0.0f), mW(0.0f) {}
                Vec4(const Vec4& other): mX(other.mX), mY(other.mY), mZ(other.mZ), mW(other.mW) {}
    explicit    Vec4(const Vec2& other): mX(other.mX), mY(other.mY), mZ(0.0f), mW(0.0f) {}
    explicit    Vec4(const Vec3& other): mX(other.mX), mY(other.mY), mZ(other.mZ), mW(0.0f) {}
                Vec4(float fX, float fY, float fZ, float fW): mX(fX), mY(fY), mZ(fZ), mW(fW) {}

    Vec4      operator-() const {return Vec4(-mX, -mY, -mZ, -mW);}
    float       operator*(const Vec4& other) const {return mX * other.mX + mY * other.mY + mZ * other.mZ + mW * other.mW;} // Dot product.
    Vec4      operator-(const Vec4& other) const {return Vec4(mX - other.mX, mY - other.mY, mZ - other.mZ, mW - other.mW);}
    Vec4      operator+(const Vec4& other) const {return Vec4(mX + other.mX, mY + other.mY, mZ + other.mZ, mW + other.mW);}
    Vec4&     operator=(const Vec4& other) {mX = other.mX; mY = other.mY; mZ = other.mZ; mW = other.mW; return *this;}
    Vec4&     operator=(const Vec3& other) {mX = other.mX; mY = other.mY; mZ = other.mZ; mW = 0.0f; return *this;}
    Vec4&     operator=(const Vec2& other) {mX = other.mX; mY = other.mY; mZ = 0.0f; mW = 0.0f; return *this;}
    Vec4&     operator+=(const Vec4& other) {mX += other.mX; mY += other.mY; mZ += other.mZ; mW += other.mW; return *this;}
    Vec4&     operator-=(const Vec4& other) {mX -= other.mX; mY -= other.mY; mZ -= other.mZ; mW -= other.mW; return *this;}
    Vec4&     operator*=(float value) {mX *= value; mY *= value; mZ *= value; mW *= value; return *this;}
    Vec4      operator*(float value) const {return Vec4(mX * value, mY * value, mZ * value, mW * value);}
    Vec4&     operator/=(float value) {mX /= value; mY /= value; mZ /= value; mW /= value; return *this;}
    Vec4      operator/(float value) const {return Vec4(mX / value, mY / value, mZ / value, mW / value);}
    Vec4&     operator*=(const class Mat4& matrix);
    float       operator[](int index) const {return (&mX)[index];}
    float&      operator[](int index) {return (&mX)[index];}
    bool        operator==(const Vec4& other) const {return Util::Approximately(mX, other.mX) && Util::Approximately(mY, other.mY) && Util::Approximately(mZ, other.mZ) && Util::Approximately(mW, other.mW);}
    bool        operator!=(const Vec4& other) const {return !Util::Approximately(mX, other.mX) || !Util::Approximately(mY, other.mY) || !Util::Approximately(mZ, other.mZ) || !Util::Approximately(mW, other.mW);}

    void        Set(float fX, float fY, float fZ, float fW) {mX = fX; mY = fY; mZ = fZ; mW = fW;}
    float       Distance(const Vec4& other) const {return (*this - other).Length();}
    float       Length() const {return std::sqrt(mX * mX + mY * mY + mZ * mZ + mW * mW);}
    float       Normalize();
    void        Zero() {mX = 0.0f; mY = 0.0f; mZ = 0.0f; mW = 0.0f;}
};

inline float Vec4::Normalize()
{
    float length = Length();

    if(length > 0.0f)
    {
        mX /= length;
        mY /= length;
        mZ /= length;
        mW /= length;
    }

    return length;
}

}