

//
// 4x4 matrix is useful for homogeneous transformations, mostly for rotations.
//

#pragma once

#include <Math/GluUtils.h>

namespace ftr {

class _ALIGN(16) Mat4
{
public:
    static const Mat4 Zero;
    static const Mat4 Identity;
    /*
     [row][column]
     [0][0], [0][1], [0][2], [0][3]
     [1][0], [1][1], [1][2], [1][3]
     [2][0], [2][1], [2][2], [2][3]
     [3][0], [3][1], [3][2], [3][3]
    */
    Vec4              mX;
    Vec4              mY;
    Vec4              mZ;
    Vec4              mW;

                      Mat4(): mX(1.0f, 0.0f, 0.0f, 0.0f), mY(0.0f, 1.0f, 0.0f, 0.0f), mZ(0.0f, 0.0f, 1.0f, 0.0f), mW(0.0f, 0.0f, 0.0f, 1.0f) {}
                      Mat4(const Mat4& other): mX(other.mX), mY(other.mY), mZ(other.mZ), mW(other.mW) {}
                      Mat4(const Vec4& vX, const Vec4& vY, const Vec4& vZ, const Vec4& vW): mX(vX), mY(vY), mZ(vZ), mW(vW) {}

    Mat4              operator-() const {return Mat4(-mX, -mY, -mZ, -mW);}
    Mat4              operator-(const Mat4& other) const {return Mat4(mX - other.mX, mY - other.mY, mZ - other.mZ, mW - other.mW);}
    Mat4              operator+(const Mat4& other) const {return Mat4(mX + other.mX, mY + other.mY, mZ + other.mZ, mW + other.mW);}
    Mat4&             operator=(const Mat4& other) {mX = other.mX; mY = other.mY; mZ = other.mZ; mW = other.mW; return *this;}
    Mat4&             operator+=(const Mat4& other) {mX += other.mX; mY += other.mY; mZ += other.mZ; mW += other.mW; return *this;}
    Mat4&             operator-=(const Mat4& other) {mX -= other.mX; mY -= other.mY; mZ -= other.mZ; mW -= other.mW; return *this;}
    Mat4&             operator*=(float value) {mX *= value; mY *= value; mZ *= value; mW *= value; return *this;}
    Mat4              operator*(float value) const {return Mat4(mX * value, mY * value, mZ * value, mW * value);}
    Mat4&             operator*=(const Mat4& other);
    Mat4              operator*(const Mat4& other) const;
    const Vec4&       operator[](int index) const {return (&mX)[index];}
    Vec4&             operator[](int index) {return (&mX)[index];}
    bool              operator==(const Mat4& other) const {return mX == other.mX && mY == other.mY && mZ == other.mZ && mW == other.mW;}
    bool              operator!=(const Mat4& other) const {return mX != other.mX || mY != other.mY || mZ != other.mZ || mW != other.mW;}

    void              set(const Vec4& vX, const Vec4& vY, const Vec4& vZ, const Vec4& vW) {mX = vX; mY = vY; mZ = vZ; mW = vW;}
    void              Orthonormalize();
    Mat4              Transpose() const;
    Mat4              Invert() const;
    void              setArray(float* a);
    void              DoubleArray(double* array) const;
};
    

inline void Mat4::DoubleArray(double* array) const
{
    const int matrixSize = 4;
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            int index = i*matrixSize + j;
            array[index] = static_cast<double>((*this)[i][j]);
        }
    }
}
    
inline void Mat4::setArray(float* a)
{
    mX[0] = a[0]; mX[1] = a[1]; mX[2] = a[2]; mX[3] = a[3];
    mY[0] = a[4]; mY[1] = a[5]; mY[2] = a[6]; mY[3] = a[7];
    mZ[0] = a[8]; mZ[1] = a[9]; mZ[2] = a[10]; mZ[3] = a[11];
    mW[0] = a[12]; mW[1] = a[13]; mW[2] = a[14]; mW[3] = a[15];
}


inline Mat4 Mat4::operator*(const Mat4& other) const
{
    //
    // Row 0.
    //
    float fA = mX[0] * other.mX[0] + mX[1] * other.mY[0] + mX[2] * other.mZ[0] + mX[3] * other.mW[0];
    float fB = mX[0] * other.mX[1] + mX[1] * other.mY[1] + mX[2] * other.mZ[1] + mX[3] * other.mW[1];
    float fC = mX[0] * other.mX[2] + mX[1] * other.mY[2] + mX[2] * other.mZ[2] + mX[3] * other.mW[2];
    float fD = mX[0] * other.mX[3] + mX[1] * other.mY[3] + mX[2] * other.mZ[3] + mX[3] * other.mW[3];

    //
    // Row 1.
    //
    float fE = mY[0] * other.mX[0] + mY[1] * other.mY[0] + mY[2] * other.mZ[0] + mY[3] * other.mW[0];
    float fF = mY[0] * other.mX[1] + mY[1] * other.mY[1] + mY[2] * other.mZ[1] + mY[3] * other.mW[1];
    float fG = mY[0] * other.mX[2] + mY[1] * other.mY[2] + mY[2] * other.mZ[2] + mY[3] * other.mW[2];
    float fH = mY[0] * other.mX[3] + mY[1] * other.mY[3] + mY[2] * other.mZ[3] + mY[3] * other.mW[3];

    //
    // Row 2.
    //
    float fI = mZ[0] * other.mX[0] + mZ[1] * other.mY[0] + mZ[2] * other.mZ[0] + mZ[3] * other.mW[0];
    float fJ = mZ[0] * other.mX[1] + mZ[1] * other.mY[1] + mZ[2] * other.mZ[1] + mZ[3] * other.mW[1];
    float k = mZ[0] * other.mX[2] + mZ[1] * other.mY[2] + mZ[2] * other.mZ[2] + mZ[3] * other.mW[2];
    float fL = mZ[0] * other.mX[3] + mZ[1] * other.mY[3] + mZ[2] * other.mZ[3] + mZ[3] * other.mW[3];

    //
    // Row 3.
    //
    float m = mW[0] * other.mX[0] + mW[1] * other.mY[0] + mW[2] * other.mZ[0] + mW[3] * other.mW[0];
    float fN = mW[0] * other.mX[1] + mW[1] * other.mY[1] + mW[2] * other.mZ[1] + mW[3] * other.mW[1];
    float fO = mW[0] * other.mX[2] + mW[1] * other.mY[2] + mW[2] * other.mZ[2] + mW[3] * other.mW[2];
    float fP = mW[0] * other.mX[3] + mW[1] * other.mY[3] + mW[2] * other.mZ[3] + mW[3] * other.mW[3];

    return Mat4(Vec4(fA, fB, fC, fD),
        Vec4(fE, fF, fG, fH),
        Vec4(fI, fJ, k, fL),
        Vec4(m, fN, fO, fP));
}

inline Mat4& Mat4::operator*=(const Mat4& other)
{
    //
    // Row 0.
    //
    float fA = mX[0] * other.mX[0] + mX[1] * other.mY[0] + mX[2] * other.mZ[0] + mX[3] * other.mW[0];
    float fB = mX[0] * other.mX[1] + mX[1] * other.mY[1] + mX[2] * other.mZ[1] + mX[3] * other.mW[1];
    float fC = mX[0] * other.mX[2] + mX[1] * other.mY[2] + mX[2] * other.mZ[2] + mX[3] * other.mW[2];
    float fD = mX[0] * other.mX[3] + mX[1] * other.mY[3] + mX[2] * other.mZ[3] + mX[3] * other.mW[3];

    //
    // Row 1.
    //
    float fE = mY[0] * other.mX[0] + mY[1] * other.mY[0] + mY[2] * other.mZ[0] + mY[3] * other.mW[0];
    float fF = mY[0] * other.mX[1] + mY[1] * other.mY[1] + mY[2] * other.mZ[1] + mY[3] * other.mW[1];
    float fG = mY[0] * other.mX[2] + mY[1] * other.mY[2] + mY[2] * other.mZ[2] + mY[3] * other.mW[2];
    float fH = mY[0] * other.mX[3] + mY[1] * other.mY[3] + mY[2] * other.mZ[3] + mY[3] * other.mW[3];

    //
    // Row 2.
    //
    float fI = mZ[0] * other.mX[0] + mZ[1] * other.mY[0] + mZ[2] * other.mZ[0] + mZ[3] * other.mW[0];
    float fJ = mZ[0] * other.mX[1] + mZ[1] * other.mY[1] + mZ[2] * other.mZ[1] + mZ[3] * other.mW[1];
    float k = mZ[0] * other.mX[2] + mZ[1] * other.mY[2] + mZ[2] * other.mZ[2] + mZ[3] * other.mW[2];
    float fL = mZ[0] * other.mX[3] + mZ[1] * other.mY[3] + mZ[2] * other.mZ[3] + mZ[3] * other.mW[3];

    //
    // Row 3.
    //
    float m = mW[0] * other.mX[0] + mW[1] * other.mY[0] + mW[2] * other.mZ[0] + mW[3] * other.mW[0];
    float fN = mW[0] * other.mX[1] + mW[1] * other.mY[1] + mW[2] * other.mZ[1] + mW[3] * other.mW[1];
    float fO = mW[0] * other.mX[2] + mW[1] * other.mY[2] + mW[2] * other.mZ[2] + mW[3] * other.mW[2];
    float fP = mW[0] * other.mX[3] + mW[1] * other.mY[3] + mW[2] * other.mZ[3] + mW[3] * other.mW[3];

    //
    // Row 0.
    //
    mX[0] = fA;
    mX[1] = fB;
    mX[2] = fC;
    mX[3] = fD;

    //
    // Row 1.
    //
    mY[0] = fE;
    mY[1] = fF;
    mY[2] = fG;
    mY[3] = fH;

    //
    // Row 2.
    //
    mZ[0] = fI;
    mZ[1] = fJ;
    mZ[2] = k;
    mZ[3] = fL;

    //
    // Row 3.
    //
    mW[0] = m;
    mW[1] = fN;
    mW[2] = fO;
    mW[3] = fP;

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
    float x = mX;
    float y = mY;
    float z = mZ;

    mX = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] + matrix[3][0];
    mY = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] + matrix[3][1];
    mZ = x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] + matrix[3][2];

    return *this;
}

inline Vec4& Vec4::operator*=(const Mat4& matrix)
{
    float x = mX;
    float y = mY;
    float z = mZ;
    float w = mW;

    mX = x * matrix[0][0] + y * matrix[1][0] + z * matrix[2][0] + w * matrix[3][0];
    mY = x * matrix[0][1] + y * matrix[1][1] + z * matrix[2][1] + w * matrix[3][1];
    mZ = x * matrix[0][2] + y * matrix[1][2] + z * matrix[2][2] + w * matrix[3][2];
    mW = x * matrix[0][3] + y * matrix[1][3] + z * matrix[2][3] + w * matrix[3][3];

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
    mX.Normalize();

    //
    // Forward.
    //
    mZ = Vec3(mX[0], mX[1], mX[2]) ^ Vec3(mY[0], mY[1], mY[2]);
    mZ.Normalize();

    //
    // Up.
    //
    mY = Vec3(mZ[0], mZ[1], mZ[2]) ^ Vec3(mX[0], mX[1], mX[2]);
    mY.Normalize();
}

inline Mat4 Mat4::Transpose() const
{
    return Mat4(Vec4(mX[0], mY[0], mZ[0], mW[0]),
        Vec4(mX[1], mY[1], mZ[1], mW[1]),
        Vec4(mX[2], mY[2], mZ[2], mW[2]),
        Vec4(mX[3], mY[3], mZ[3], mW[3]));
}
    
inline Mat4 Mat4::Invert() const
{
    Mat4 result;
    int matrixIsInvertable = GluUtils::glhInvertMatrixf2(reinterpret_cast<const float*>(this),
                                                         reinterpret_cast<float*>(&result));
    assert(matrixIsInvertable);
    return result;
}
    
}