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

    Vec2              m_vX;
    Vec2              m_vY;

                        Mat2(): m_vX(1.0f, 0.0f), m_vY(0.0f, 1.0f) {}
                        Mat2(const Mat2& other): m_vX(other.m_vX), m_vY(other.m_vY) {}
                        Mat2(const Vec2& vX, const Vec2& vY): m_vX(vX), m_vY(vY) {}

    Mat2              operator-() const {return Mat2(-m_vX, -m_vY);}
    Mat2              operator-(const Mat2& other) const {return Mat2(m_vX - other.m_vX, m_vY - other.m_vY);}
    Mat2              operator+(const Mat2& other) const {return Mat2(m_vX + other.m_vX, m_vY + other.m_vY);}
    Mat2&             operator=(const Mat2& other) {m_vX = other.m_vX; m_vY = other.m_vY; return *this;}
    Mat2&             operator+=(const Mat2& other) {m_vX += other.m_vX; m_vY += other.m_vY; return *this;}
    Mat2&             operator-=(const Mat2& other) {m_vX -= other.m_vX; m_vY -= other.m_vY; return *this;}
    Mat2&             operator*=(float value) {m_vX *= value; m_vY *= value; return *this;}
    Mat2              operator*(float value) const {return Mat2(m_vX * value, m_vY * value);}
    Mat2&             operator*=(const Mat2& other);
    Mat2              operator*(const Mat2& other) const;
    const Vec2&       operator[](int index) const {return (&m_vX)[index];}
    Vec2&             operator[](int index) {return (&m_vX)[index];}
    bool                operator==(const Mat2& other) const {return m_vX == other.m_vX && m_vY == other.m_vY;}
    bool                operator!=(const Mat2& other) const {return m_vX != other.m_vX || m_vY != other.m_vY;}

    void                Set(const Vec2& vX, const Vec2& vY) {m_vX = vX; m_vY = vY;}
    Mat2              Transpose() const {return Mat2(Vec2(m_vX[0], m_vY[0]), Vec2(m_vX[1], m_vY[1]));}
    Mat2              Rotate(float fAngle) const;
};

inline Mat2 Mat2::operator*(const Mat2& other) const
{
    float fA = m_vX[0] * other[0][0] + m_vX[1] * other[1][0];
    float fB = m_vX[0] * other[0][1] + m_vX[1] * other[1][1];
    float fC = m_vY[0] * other[0][0] + m_vY[1] * other[1][0];
    float fD = m_vY[0] * other[0][1] + m_vY[1] * other[1][1];

    return Mat2(Vec2(fA, fB), Vec2(fC, fD));
}

inline Mat2& Mat2::operator*=(const Mat2& other)
{
    float fA = m_vX[0] * other[0][0] + m_vX[1] * other[1][0];
    float fB = m_vX[0] * other[0][1] + m_vX[1] * other[1][1];
    float fC = m_vY[0] * other[0][0] + m_vY[1] * other[1][0];
    float fD = m_vY[0] * other[0][1] + m_vY[1] * other[1][1];

    m_vX[0] = fA;
    m_vX[1] = fB;
    m_vY[0] = fC;
    m_vY[1] = fD;

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

    float fA = m_vX[0] * fAlpha - m_vX[1] * fBeta;
    float fB = m_vX[1] * fAlpha + m_vX[0] * fBeta;
    float fC = m_vY[0] * fAlpha - m_vY[1] * fBeta;
    float fD = m_vY[1] * fAlpha + m_vY[0] * fBeta;

    return Mat2(Vec2(fA, fB), Vec2(fC, fD));
}

inline Vec2& Vec2::operator*=(const Mat2& matrix)
{
    float fX = mX;
    float fY = mY;

    mX = fX * matrix[0][0] + fY * matrix[1][0];
    mY = fX * matrix[0][1] + fY * matrix[1][1];

    return *this;
}

}