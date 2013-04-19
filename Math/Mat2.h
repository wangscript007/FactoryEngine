//
// Copyright (c) On5. All rights reserved.
//

//
// 2x2 matrix is useful for 2d transformations, mostly for rotations.
// To rotate a frame or vector, multiply it by rotated existing or
// identity matrix.
//

namespace ftr {

#pragma once

class _ALIGN(16) Mat2
{
public:
    static const Mat2 Zero;
    static const Mat2 Identity;

    Vec2              mX;
    Vec2              mY;

                        Mat2(): mX(1.0f, 0.0f), mY(0.0f, 1.0f) {}
                        Mat2(const Mat2& other): mX(other.mX), mY(other.mY) {}
                        Mat2(const Vec2& vX, const Vec2& vY): mX(vX), mY(vY) {}

    Mat2              operator-() const {return Mat2(-mX, -mY);}
    Mat2              operator-(const Mat2& other) const {return Mat2(mX - other.mX, mY - other.mY);}
    Mat2              operator+(const Mat2& other) const {return Mat2(mX + other.mX, mY + other.mY);}
    Mat2&             operator=(const Mat2& other) {mX = other.mX; mY = other.mY; return *this;}
    Mat2&             operator+=(const Mat2& other) {mX += other.mX; mY += other.mY; return *this;}
    Mat2&             operator-=(const Mat2& other) {mX -= other.mX; mY -= other.mY; return *this;}
    Mat2&             operator*=(float value) {mX *= value; mY *= value; return *this;}
    Mat2              operator*(float value) const {return Mat2(mX * value, mY * value);}
    Mat2&             operator*=(const Mat2& other);
    Mat2              operator*(const Mat2& other) const;
    const Vec2&       operator[](int index) const {return (&mX)[index];}
    Vec2&             operator[](int index) {return (&mX)[index];}
    bool                operator==(const Mat2& other) const {return mX == other.mX && mY == other.mY;}
    bool                operator!=(const Mat2& other) const {return mX != other.mX || mY != other.mY;}

    void                set(const Vec2& vX, const Vec2& vY) {mX = vX; mY = vY;}
    Mat2              Transpose() const {return Mat2(Vec2(mX[0], mY[0]), Vec2(mX[1], mY[1]));}
    Mat2              Rotate(float fAngle) const;
};

inline Mat2 Mat2::operator*(const Mat2& other) const
{
    float fA = mX[0] * other[0][0] + mX[1] * other[1][0];
    float fB = mX[0] * other[0][1] + mX[1] * other[1][1];
    float fC = mY[0] * other[0][0] + mY[1] * other[1][0];
    float fD = mY[0] * other[0][1] + mY[1] * other[1][1];

    return Mat2(Vec2(fA, fB), Vec2(fC, fD));
}

inline Mat2& Mat2::operator*=(const Mat2& other)
{
    float fA = mX[0] * other[0][0] + mX[1] * other[1][0];
    float fB = mX[0] * other[0][1] + mX[1] * other[1][1];
    float fC = mY[0] * other[0][0] + mY[1] * other[1][0];
    float fD = mY[0] * other[0][1] + mY[1] * other[1][1];

    mX[0] = fA;
    mX[1] = fB;
    mY[0] = fC;
    mY[1] = fD;

    return *this;
}

inline Vec2 operator*(const Vec2& vector, const Mat2& matrix)
{
    return Vec2(vector[0] * matrix[0][0] + vector[1] * matrix[1][0], vector[0] * matrix[0][1] + vector[1] * matrix[1][1]);
}

inline Vec2 operator*(const Mat2& matrix, const Vec2& vector)
{
    return Vec2(vector[0] * matrix[0][0] + vector[1] * matrix[1][0], vector[0] * matrix[0][1] + vector[1] * matrix[1][1]);
}

inline Mat2 Mat2::Rotate(float fAngle) const
{
    float fAlpha = std::cos(fAngle);
    float fBeta = std::sin(fAngle);

    float fA = mX[0] * fAlpha - mX[1] * fBeta;
    float fB = mX[1] * fAlpha + mX[0] * fBeta;
    float fC = mY[0] * fAlpha - mY[1] * fBeta;
    float fD = mY[1] * fAlpha + mY[0] * fBeta;

    return Mat2(Vec2(fA, fB), Vec2(fC, fD));
}

inline Vec2& Vec2::operator*=(const Mat2& matrix)
{
    float x = mX;
    float y = mY;

    mX = x * matrix[0][0] + y * matrix[1][0];
    mY = x * matrix[0][1] + y * matrix[1][1];

    return *this;
}

}