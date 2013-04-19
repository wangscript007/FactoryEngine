//
// Copyright (c) On5. All rights reserved.
//

//
// 4x4 matrix is useful for homogeneous transformations, mostly for rotations.
//

#pragma once

namespace ftr {

class _ALIGN(16) Mat4
{
public:
    static const Mat4 Zero;
    static const Mat4 Identity;

    Vec4              m_vX;
    Vec4              m_vY;
    Vec4              m_vZ;
    Vec4              m_vW;

                        Mat4(): m_vX(1.0f, 0.0f, 0.0f, 0.0f), m_vY(0.0f, 1.0f, 0.0f, 0.0f), m_vZ(0.0f, 0.0f, 1.0f, 0.0f), m_vW(0.0f, 0.0f, 0.0f, 1.0f) {}
                        Mat4(const Mat4& other): m_vX(other.m_vX), m_vY(other.m_vY), m_vZ(other.m_vZ), m_vW(other.m_vW) {}
                        Mat4(const Vec4& vX, const Vec4& vY, const Vec4& vZ, const Vec4& vW): m_vX(vX), m_vY(vY), m_vZ(vZ), m_vW(vW) {}

    Mat4              operator-() const {return Mat4(-m_vX, -m_vY, -m_vZ, -m_vW);}
    Mat4              operator-(const Mat4& other) const {return Mat4(m_vX - other.m_vX, m_vY - other.m_vY, m_vZ - other.m_vZ, m_vW - other.m_vW);}
    Mat4              operator+(const Mat4& other) const {return Mat4(m_vX + other.m_vX, m_vY + other.m_vY, m_vZ + other.m_vZ, m_vW + other.m_vW);}
    Mat4&             operator=(const Mat4& other) {m_vX = other.m_vX; m_vY = other.m_vY; m_vZ = other.m_vZ; m_vW = other.m_vW; return *this;}
    Mat4&             operator+=(const Mat4& other) {m_vX += other.m_vX; m_vY += other.m_vY; m_vZ += other.m_vZ; m_vW += other.m_vW; return *this;}
    Mat4&             operator-=(const Mat4& other) {m_vX -= other.m_vX; m_vY -= other.m_vY; m_vZ -= other.m_vZ; m_vW -= other.m_vW; return *this;}
    Mat4&             operator*=(float value) {m_vX *= value; m_vY *= value; m_vZ *= value; m_vW *= value; return *this;}
    Mat4              operator*(float value) const {return Mat4(m_vX * value, m_vY * value, m_vZ * value, m_vW * value);}
    Mat4&             operator*=(const Mat4& other);
    Mat4              operator*(const Mat4& other) const;
    const Vec4&       operator[](int index) const {return (&m_vX)[index];}
    Vec4&             operator[](int index) {return (&m_vX)[index];}
    bool                operator==(const Mat4& other) const {return m_vX == other.m_vX && m_vY == other.m_vY && m_vZ == other.m_vZ && m_vW == other.m_vW;}
    bool                operator!=(const Mat4& other) const {return m_vX != other.m_vX || m_vY != other.m_vY || m_vZ != other.m_vZ || m_vW != other.m_vW;}

    void                Set(const Vec4& vX, const Vec4& vY, const Vec4& vZ, const Vec4& vW) {m_vX = vX; m_vY = vY; m_vZ = vZ; m_vW = vW;}
    void                Orthonormalize();
    Mat4              Transpose() const;
};

inline Mat4 Mat4::operator*(const Mat4& other) const
{
    //
    // Row 0.
    //
    float fA = m_vX[0] * other.m_vX[0] + m_vX[1] * other.m_vY[0] + m_vX[2] * other.m_vZ[0] + m_vX[3] * other.m_vW[0];
    float fB = m_vX[0] * other.m_vX[1] + m_vX[1] * other.m_vY[1] + m_vX[2] * other.m_vZ[1] + m_vX[3] * other.m_vW[1];
    float fC = m_vX[0] * other.m_vX[2] + m_vX[1] * other.m_vY[2] + m_vX[2] * other.m_vZ[2] + m_vX[3] * other.m_vW[2];
    float fD = m_vX[0] * other.m_vX[3] + m_vX[1] * other.m_vY[3] + m_vX[2] * other.m_vZ[3] + m_vX[3] * other.m_vW[3];

    //
    // Row 1.
    //
    float fE = m_vY[0] * other.m_vX[0] + m_vY[1] * other.m_vY[0] + m_vY[2] * other.m_vZ[0] + m_vY[3] * other.m_vW[0];
    float fF = m_vY[0] * other.m_vX[1] + m_vY[1] * other.m_vY[1] + m_vY[2] * other.m_vZ[1] + m_vY[3] * other.m_vW[1];
    float fG = m_vY[0] * other.m_vX[2] + m_vY[1] * other.m_vY[2] + m_vY[2] * other.m_vZ[2] + m_vY[3] * other.m_vW[2];
    float fH = m_vY[0] * other.m_vX[3] + m_vY[1] * other.m_vY[3] + m_vY[2] * other.m_vZ[3] + m_vY[3] * other.m_vW[3];

    //
    // Row 2.
    //
    float fI = m_vZ[0] * other.m_vX[0] + m_vZ[1] * other.m_vY[0] + m_vZ[2] * other.m_vZ[0] + m_vZ[3] * other.m_vW[0];
    float fJ = m_vZ[0] * other.m_vX[1] + m_vZ[1] * other.m_vY[1] + m_vZ[2] * other.m_vZ[1] + m_vZ[3] * other.m_vW[1];
    float fK = m_vZ[0] * other.m_vX[2] + m_vZ[1] * other.m_vY[2] + m_vZ[2] * other.m_vZ[2] + m_vZ[3] * other.m_vW[2];
    float fL = m_vZ[0] * other.m_vX[3] + m_vZ[1] * other.m_vY[3] + m_vZ[2] * other.m_vZ[3] + m_vZ[3] * other.m_vW[3];

    //
    // Row 3.
    //
    float fM = m_vW[0] * other.m_vX[0] + m_vW[1] * other.m_vY[0] + m_vW[2] * other.m_vZ[0] + m_vW[3] * other.m_vW[0];
    float fN = m_vW[0] * other.m_vX[1] + m_vW[1] * other.m_vY[1] + m_vW[2] * other.m_vZ[1] + m_vW[3] * other.m_vW[1];
    float fO = m_vW[0] * other.m_vX[2] + m_vW[1] * other.m_vY[2] + m_vW[2] * other.m_vZ[2] + m_vW[3] * other.m_vW[2];
    float fP = m_vW[0] * other.m_vX[3] + m_vW[1] * other.m_vY[3] + m_vW[2] * other.m_vZ[3] + m_vW[3] * other.m_vW[3];

    return Mat4(Vec4(fA, fB, fC, fD),
        Vec4(fE, fF, fG, fH),
        Vec4(fI, fJ, fK, fL),
        Vec4(fM, fN, fO, fP));
}

inline Mat4& Mat4::operator*=(const Mat4& other)
{
    //
    // Row 0.
    //
    float fA = m_vX[0] * other.m_vX[0] + m_vX[1] * other.m_vY[0] + m_vX[2] * other.m_vZ[0] + m_vX[3] * other.m_vW[0];
    float fB = m_vX[0] * other.m_vX[1] + m_vX[1] * other.m_vY[1] + m_vX[2] * other.m_vZ[1] + m_vX[3] * other.m_vW[1];
    float fC = m_vX[0] * other.m_vX[2] + m_vX[1] * other.m_vY[2] + m_vX[2] * other.m_vZ[2] + m_vX[3] * other.m_vW[2];
    float fD = m_vX[0] * other.m_vX[3] + m_vX[1] * other.m_vY[3] + m_vX[2] * other.m_vZ[3] + m_vX[3] * other.m_vW[3];

    //
    // Row 1.
    //
    float fE = m_vY[0] * other.m_vX[0] + m_vY[1] * other.m_vY[0] + m_vY[2] * other.m_vZ[0] + m_vY[3] * other.m_vW[0];
    float fF = m_vY[0] * other.m_vX[1] + m_vY[1] * other.m_vY[1] + m_vY[2] * other.m_vZ[1] + m_vY[3] * other.m_vW[1];
    float fG = m_vY[0] * other.m_vX[2] + m_vY[1] * other.m_vY[2] + m_vY[2] * other.m_vZ[2] + m_vY[3] * other.m_vW[2];
    float fH = m_vY[0] * other.m_vX[3] + m_vY[1] * other.m_vY[3] + m_vY[2] * other.m_vZ[3] + m_vY[3] * other.m_vW[3];

    //
    // Row 2.
    //
    float fI = m_vZ[0] * other.m_vX[0] + m_vZ[1] * other.m_vY[0] + m_vZ[2] * other.m_vZ[0] + m_vZ[3] * other.m_vW[0];
    float fJ = m_vZ[0] * other.m_vX[1] + m_vZ[1] * other.m_vY[1] + m_vZ[2] * other.m_vZ[1] + m_vZ[3] * other.m_vW[1];
    float fK = m_vZ[0] * other.m_vX[2] + m_vZ[1] * other.m_vY[2] + m_vZ[2] * other.m_vZ[2] + m_vZ[3] * other.m_vW[2];
    float fL = m_vZ[0] * other.m_vX[3] + m_vZ[1] * other.m_vY[3] + m_vZ[2] * other.m_vZ[3] + m_vZ[3] * other.m_vW[3];

    //
    // Row 3.
    //
    float fM = m_vW[0] * other.m_vX[0] + m_vW[1] * other.m_vY[0] + m_vW[2] * other.m_vZ[0] + m_vW[3] * other.m_vW[0];
    float fN = m_vW[0] * other.m_vX[1] + m_vW[1] * other.m_vY[1] + m_vW[2] * other.m_vZ[1] + m_vW[3] * other.m_vW[1];
    float fO = m_vW[0] * other.m_vX[2] + m_vW[1] * other.m_vY[2] + m_vW[2] * other.m_vZ[2] + m_vW[3] * other.m_vW[2];
    float fP = m_vW[0] * other.m_vX[3] + m_vW[1] * other.m_vY[3] + m_vW[2] * other.m_vZ[3] + m_vW[3] * other.m_vW[3];

    //
    // Row 0.
    //
    m_vX[0] = fA;
    m_vX[1] = fB;
    m_vX[2] = fC;
    m_vX[3] = fD;

    //
    // Row 1.
    //
    m_vY[0] = fE;
    m_vY[1] = fF;
    m_vY[2] = fG;
    m_vY[3] = fH;

    //
    // Row 2.
    //
    m_vZ[0] = fI;
    m_vZ[1] = fJ;
    m_vZ[2] = fK;
    m_vZ[3] = fL;

    //
    // Row 3.
    //
    m_vW[0] = fM;
    m_vW[1] = fN;
    m_vW[2] = fO;
    m_vW[3] = fP;

    return *this;
}

inline Vec3 operator*(const Vec3& vector, const Mat4& matrix)
{
    return Vec3(
        vector[0] * matrix[0][0] + vector[1] * matrix[1][0] + vector[2] * matrix[2][0] + matrix[3][0],
        vector[0] * matrix[0][1] + vector[1] * matrix[1][1] + vector[2] * matrix[2][1] + matrix[3][1],
        vector[0] * matrix[0][2] + vector[1] * matrix[1][2] + vector[2] * matrix[2][2] + matrix[3][2]);
}

inline Vec3 operator*(const Mat4& matrix, const Vec3& vector)
{
    return Vec3(
        vector[0] * matrix[0][0] + vector[1] * matrix[1][0] + vector[2] * matrix[2][0] + matrix[3][0],
        vector[0] * matrix[0][1] + vector[1] * matrix[1][1] + vector[2] * matrix[2][1] + matrix[3][1],
        vector[0] * matrix[0][2] + vector[1] * matrix[1][2] + vector[2] * matrix[2][2] + matrix[3][2]);
}

inline Vec3& Vec3::operator*=(const Mat4& matrix)
{
    float fX = mX;
    float fY = mY;
    float fZ = mZ;

    mX = fX * matrix[0][0] + fY * matrix[1][0] + fZ * matrix[2][0] + matrix[3][0];
    mY = fX * matrix[0][1] + fY * matrix[1][1] + fZ * matrix[2][1] + matrix[3][1];
    mZ = fX * matrix[0][2] + fY * matrix[1][2] + fZ * matrix[2][2] + matrix[3][2];

    return *this;
}

inline Vec4& Vec4::operator*=(const Mat4& matrix)
{
    float fX = mX;
    float fY = mY;
    float fZ = mZ;
    float fW = mW;

    mX = fX * matrix[0][0] + fY * matrix[1][0] + fZ * matrix[2][0] + fW * matrix[3][0];
    mY = fX * matrix[0][1] + fY * matrix[1][1] + fZ * matrix[2][1] + fW * matrix[3][1];
    mZ = fX * matrix[0][2] + fY * matrix[1][2] + fZ * matrix[2][2] + fW * matrix[3][2];
    mW = fX * matrix[0][3] + fY * matrix[1][3] + fZ * matrix[2][3] + fW * matrix[3][3];

    return *this;
}

inline Vec4 operator*(const Vec4& vector, const Mat4& matrix)
{
    return Vec4(
        vector[0] * matrix[0][0] + vector[1] * matrix[1][0] + vector[2] * matrix[2][0] + vector[3] * matrix[3][0],
        vector[0] * matrix[0][1] + vector[1] * matrix[1][1] + vector[2] * matrix[2][1] + vector[3] * matrix[3][1],
        vector[0] * matrix[0][2] + vector[1] * matrix[1][2] + vector[2] * matrix[2][2] + vector[3] * matrix[3][2],
        vector[0] * matrix[0][3] + vector[1] * matrix[1][3] + vector[2] * matrix[2][3] + vector[3] * matrix[3][3]);
}

inline Vec4 operator*(const Mat4& matrix, const Vec4& vector)
{
    return Vec4(
        vector[0] * matrix[0][0] + vector[1] * matrix[1][0] + vector[2] * matrix[2][0] + vector[3] * matrix[3][0],
        vector[0] * matrix[0][1] + vector[1] * matrix[1][1] + vector[2] * matrix[2][1] + vector[3] * matrix[3][1],
        vector[0] * matrix[0][2] + vector[1] * matrix[1][2] + vector[2] * matrix[2][2] + vector[3] * matrix[3][2],
        vector[0] * matrix[0][3] + vector[1] * matrix[1][3] + vector[2] * matrix[2][3] + vector[3] * matrix[3][3]);
}

inline void Mat4::Orthonormalize()
{
    //
    // Right.
    //
    m_vX.Normalize();

    //
    // Forward.
    //
    m_vZ = Vec3(m_vX[0], m_vX[1], m_vX[2]) ^ Vec3(m_vY[0], m_vY[1], m_vY[2]);
    m_vZ.Normalize();

    //
    // Up.
    //
    m_vY = Vec3(m_vZ[0], m_vZ[1], m_vZ[2]) ^ Vec3(m_vX[0], m_vX[1], m_vX[2]);
    m_vY.Normalize();
}

inline Mat4 Mat4::Transpose() const
{
    return Mat4(Vec4(m_vX[0], m_vY[0], m_vZ[0], m_vW[0]),
        Vec4(m_vX[1], m_vY[1], m_vZ[1], m_vW[1]),
        Vec4(m_vX[2], m_vY[2], m_vZ[2], m_vW[2]),
        Vec4(m_vX[3], m_vY[3], m_vZ[3], m_vW[3]));
}

}