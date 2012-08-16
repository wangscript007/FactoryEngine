//
// Copyright (c) On5. All rights reserved.
//

//
// 2x2 matrix is useful for 2d transformations, mostly for rotations.
// To rotate a frame or vector, multiply it by rotated existing or
// identity matrix.
//

class O5_ALIGN(16) O5Mat2
{
public:
    static const O5Mat2 Zero;
    static const O5Mat2 Identity;

    O5Vec2              m_vX;
    O5Vec2              m_vY;

                        O5Mat2(): m_vX(1.0f, 0.0f), m_vY(0.0f, 1.0f) {}
                        O5Mat2(const O5Mat2& other): m_vX(other.m_vX), m_vY(other.m_vY) {}
                        O5Mat2(const O5Vec2& vX, const O5Vec2& vY): m_vX(vX), m_vY(vY) {}

    O5Mat2              operator-() const {return O5Mat2(-m_vX, -m_vY);}
    O5Mat2              operator-(const O5Mat2& other) const {return O5Mat2(m_vX - other.m_vX, m_vY - other.m_vY);}
    O5Mat2              operator+(const O5Mat2& other) const {return O5Mat2(m_vX + other.m_vX, m_vY + other.m_vY);}
    O5Mat2&             operator=(const O5Mat2& other) {m_vX = other.m_vX; m_vY = other.m_vY; return *this;}
    O5Mat2&             operator+=(const O5Mat2& other) {m_vX += other.m_vX; m_vY += other.m_vY; return *this;}
    O5Mat2&             operator-=(const O5Mat2& other) {m_vX -= other.m_vX; m_vY -= other.m_vY; return *this;}
    O5Mat2&             operator*=(float value) {m_vX *= value; m_vY *= value; return *this;}
    O5Mat2              operator*(float value) const {return O5Mat2(m_vX * value, m_vY * value);}
    O5Mat2&             operator*=(const O5Mat2& other);
    O5Mat2              operator*(const O5Mat2& other) const;
    const O5Vec2&       operator[](int index) const {return (&m_vX)[index];}
    O5Vec2&             operator[](int index) {return (&m_vX)[index];}
    bool                operator==(const O5Mat2& other) const {return m_vX == other.m_vX && m_vY == other.m_vY;}
    bool                operator!=(const O5Mat2& other) const {return m_vX != other.m_vX || m_vY != other.m_vY;}

    void                Set(const O5Vec2& vX, const O5Vec2& vY) {m_vX = vX; m_vY = vY;}
    O5Mat2              Transpose() const {return O5Mat2(O5Vec2(m_vX[0], m_vY[0]), O5Vec2(m_vX[1], m_vY[1]));}
    O5Mat2              Rotate(float fAngle) const;
};

inline O5Mat2 O5Mat2::operator*(const O5Mat2& other) const
{
    float fA = m_vX[0] * other[0][0] + m_vX[1] * other[1][0];
    float fB = m_vX[0] * other[0][1] + m_vX[1] * other[1][1];
    float fC = m_vY[0] * other[0][0] + m_vY[1] * other[1][0];
    float fD = m_vY[0] * other[0][1] + m_vY[1] * other[1][1];

    return O5Mat2(O5Vec2(fA, fB), O5Vec2(fC, fD));
}

inline O5Mat2& O5Mat2::operator*=(const O5Mat2& other)
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

inline O5Vec2 operator*(const O5Vec2& vector, const O5Mat2& matrix)
{
    return O5Vec2(vector[0] * matrix[0][0] + vector[1] * matrix[1][0], vector[0] * matrix[0][1] + vector[1] * matrix[1][1]);
}

inline O5Vec2 operator*(const O5Mat2& matrix, const O5Vec2& vector)
{
    return O5Vec2(vector[0] * matrix[0][0] + vector[1] * matrix[1][0], vector[0] * matrix[0][1] + vector[1] * matrix[1][1]);
}

inline O5Mat2 O5Mat2::Rotate(float fAngle) const
{
    float fAlpha = std::cos(fAngle);
    float fBeta = std::sin(fAngle);

    float fA = m_vX[0] * fAlpha - m_vX[1] * fBeta;
    float fB = m_vX[1] * fAlpha + m_vX[0] * fBeta;
    float fC = m_vY[0] * fAlpha - m_vY[1] * fBeta;
    float fD = m_vY[1] * fAlpha + m_vY[0] * fBeta;

    return O5Mat2(O5Vec2(fA, fB), O5Vec2(fC, fD));
}

inline O5Vec2& O5Vec2::operator*=(const O5Mat2& matrix)
{
    float fX = m_fX;
    float fY = m_fY;

    m_fX = fX * matrix[0][0] + fY * matrix[1][0];
    m_fY = fX * matrix[0][1] + fY * matrix[1][1];

    return *this;
}
