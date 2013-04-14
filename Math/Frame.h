//
// Copyright (c) 2012 On5. All rights reserved.
//

//
// Frame rectangle has two boundaries: minimum and maximum. You can scale it,
// translate and reconstruct, perform transformations by multiplying it by 2x2
// matrix, test intersections.
//
namespace ftr {

class _ALIGN(16) Frame
{
public:
    Vec2          m_vMin;
    Vec2          m_vMax;

                    Frame() {}
                    Frame(const Frame& other): m_vMin(other.m_vMin), m_vMax(other.m_vMax) {}
                    Frame(const Vec2& vMin, const Vec2& vMax): m_vMin(vMin), m_vMax(vMax) {}

    Frame         operator-(const Vec2& vPos) const {return Frame(m_vMin - vPos, m_vMax - vPos);}
    Frame         operator+(const Vec2& vPos) const {return Frame(m_vMin + vPos, m_vMax + vPos);}
    Frame&        operator+=(const Vec2& vPos);
    Frame&        operator-=(const Vec2& vPos);
    Frame&        operator=(const Frame& other);
    Frame&        operator*=(const Mat2& matrix);
    Frame         operator*(float fX) const {return Frame(m_vMin * fX, m_vMax * fX);}
    Frame&        operator*=(float fX);
    Vec2&         operator[](int index) {return (&m_vMin)[index];}
    const Vec2&   operator[](int index) const {return (&m_vMin)[index];}
    bool            operator==(const Frame& other) const {return m_vMin == other.m_vMin && m_vMax == other.m_vMax;}
    bool            operator!=(const Frame& other) const {return m_vMin != other.m_vMin || m_vMax != other.m_vMax;}

    void            Set(const Vec2& vMin, const Vec2& vMax);
    float           GetWidth() const {return m_vMax.m_fX - m_vMin.m_fX;}
    float           GetHeight() const {return m_vMax.m_fY - m_vMin.m_fY;}
    void            SetWidth(float fWidth) {m_vMax.m_fX = m_vMin.m_fX + fWidth;}
    void            SetHeight(float fHeight) {m_vMax.m_fY = m_vMin.m_fY + fHeight;}
    void            SetPosition(const Vec2& vPos);
    void            Scale(const Vec2& vScale);
    const Vec2&   GetPosition() const {return m_vMin;}
    void            SetExtent(const Vec2& vExtent);
    Vec2          GetExtent() const {return Vec2(GetWidth(), GetHeight());}
    bool            Intersect(const Vec2& vPoint) const;
    bool            Intersect(const Frame& other) const {return Intersect(other[0]) && Intersect(other[1]);}
    bool            Overlap(const Frame& other) const;
    Vec2          Center() const {return (m_vMin + m_vMax) * 0.5f;}
    Mat3x2        Orthographic() const;
};

inline Frame& Frame::operator=(const Frame& other)
{
    m_vMin = other.m_vMin;
    m_vMax = other.m_vMax;
    return *this;
}

inline Frame& Frame::operator-=(const Vec2& vPos)
{
    m_vMin -= vPos;
    m_vMax -= vPos;
    return *this;
}

inline Frame& Frame::operator+=(const Vec2& vPos)
{
    m_vMin += vPos;
    m_vMax += vPos;
    return *this;
}

inline void Frame::Set(const Vec2& vMin, const Vec2& vMax)
{
    m_vMin = vMin;
    m_vMax = vMax;
}

inline void Frame::SetExtent(const Vec2& vExtent)
{
    SetWidth(vExtent[0]);
    SetHeight(vExtent[1]);
}

inline void Frame::SetPosition(const Vec2& vPos)
{
    float fWidth = GetWidth();
    float fHeight = GetHeight();
    m_vMin = vPos;
    m_vMax[0] = vPos[0] + fWidth;
    m_vMax[1] = vPos[1] + fHeight;
}

inline void Frame::Scale(const Vec2& vScale)
{
    SetWidth(GetWidth() * vScale[0]);
    SetHeight(GetHeight() * vScale[1]);
}

inline bool Frame::Intersect(const Vec2& vPoint) const
{
    if(vPoint[0] < m_vMin[0])
    {
        return false;
    }
    if(vPoint[1] < m_vMin[1])
    {
        return false;
    }
    if(vPoint[0] > m_vMax[0])
    {
        return false;
    }
    if(vPoint[1] > m_vMax[1])
    {
        return false;   
    }
    return true;
}

inline bool Frame::Overlap(const Frame& other) const
{
    Vec2 vDistance = other.Center() - Center();

    if(std::abs(vDistance[0]) > (GetWidth() + other.GetWidth()) / 2.0f)
    {
        return false;
    }

    if(std::abs(vDistance[1]) > (GetHeight() + other.GetHeight()) / 2.0f)
    {
        return false;
    }

    return true;
}

inline Frame operator*(const Mat2& matrix, const Frame& frame)
{
    return Frame(frame[0] * matrix, frame[1] * matrix);
}

inline Frame operator*(const Frame& frame, const Mat2& matrix)
{
    return Frame(frame[0] * matrix, frame[1] * matrix);
}

inline Frame& Frame::operator*=(float fX)
{
    m_vMin *= fX;
    m_vMax *= fX;
    return *this;
}

inline Frame& Frame::operator*=(const Mat2& matrix)
{
    m_vMin *= matrix;
    m_vMax *= matrix;
    return *this;
}

inline Mat3x2 Frame::Orthographic() const
{
    return Mat3x2(Mat2(Vec2(2.0f / GetWidth(), 0.0f), Vec2(0.0f, 2.0f / (m_vMin[1] - m_vMax[1]))), Vec2((m_vMin[0] + m_vMax[0]) / (m_vMin[0] - m_vMax[0]), (m_vMin[1] + m_vMax[1]) / GetHeight()));
}

}