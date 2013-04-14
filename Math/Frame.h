//
// Copyright (c) 2012 On5. All rights reserved.
//

//
// Frame rectangle has two boundaries: minimum and maximum. You can scale it,
// translate and reconstruct, perform transformations by multiplying it by 2x2
// matrix, test intersections.
//

class O5_ALIGN(16) O5Frame
{
public:
    O5Vec2          m_vMin;
    O5Vec2          m_vMax;

                    O5Frame() {}
                    O5Frame(const O5Frame& other): m_vMin(other.m_vMin), m_vMax(other.m_vMax) {}
                    O5Frame(const O5Vec2& vMin, const O5Vec2& vMax): m_vMin(vMin), m_vMax(vMax) {}

    O5Frame         operator-(const O5Vec2& vPos) const {return O5Frame(m_vMin - vPos, m_vMax - vPos);}
    O5Frame         operator+(const O5Vec2& vPos) const {return O5Frame(m_vMin + vPos, m_vMax + vPos);}
    O5Frame&        operator+=(const O5Vec2& vPos);
    O5Frame&        operator-=(const O5Vec2& vPos);
    O5Frame&        operator=(const O5Frame& other);
    O5Frame&        operator*=(const O5Mat2& matrix);
    O5Frame         operator*(float fX) const {return O5Frame(m_vMin * fX, m_vMax * fX);}
    O5Frame&        operator*=(float fX);
    O5Vec2&         operator[](int index) {return (&m_vMin)[index];}
    const O5Vec2&   operator[](int index) const {return (&m_vMin)[index];}
    bool            operator==(const O5Frame& other) const {return m_vMin == other.m_vMin && m_vMax == other.m_vMax;}
    bool            operator!=(const O5Frame& other) const {return m_vMin != other.m_vMin || m_vMax != other.m_vMax;}

    void            Set(const O5Vec2& vMin, const O5Vec2& vMax);
    float           GetWidth() const {return m_vMax.m_fX - m_vMin.m_fX;}
    float           GetHeight() const {return m_vMax.m_fY - m_vMin.m_fY;}
    void            SetWidth(float fWidth) {m_vMax.m_fX = m_vMin.m_fX + fWidth;}
    void            SetHeight(float fHeight) {m_vMax.m_fY = m_vMin.m_fY + fHeight;}
    void            SetPosition(const O5Vec2& vPos);
    void            Scale(const O5Vec2& vScale);
    const O5Vec2&   GetPosition() const {return m_vMin;}
    void            SetExtent(const O5Vec2& vExtent);
    O5Vec2          GetExtent() const {return O5Vec2(GetWidth(), GetHeight());}
    bool            Intersect(const O5Vec2& vPoint) const;
    bool            Intersect(const O5Frame& other) const {return Intersect(other[0]) && Intersect(other[1]);}
    bool            Overlap(const O5Frame& other) const;
    O5Vec2          Center() const {return (m_vMin + m_vMax) * 0.5f;}
    O5Mat3x2        Orthographic() const;
};

inline O5Frame& O5Frame::operator=(const O5Frame& other)
{
    m_vMin = other.m_vMin;
    m_vMax = other.m_vMax;
    return *this;
}

inline O5Frame& O5Frame::operator-=(const O5Vec2& vPos)
{
    m_vMin -= vPos;
    m_vMax -= vPos;
    return *this;
}

inline O5Frame& O5Frame::operator+=(const O5Vec2& vPos)
{
    m_vMin += vPos;
    m_vMax += vPos;
    return *this;
}

inline void O5Frame::Set(const O5Vec2& vMin, const O5Vec2& vMax)
{
    m_vMin = vMin;
    m_vMax = vMax;
}

inline void O5Frame::SetExtent(const O5Vec2& vExtent)
{
    SetWidth(vExtent[0]);
    SetHeight(vExtent[1]);
}

inline void O5Frame::SetPosition(const O5Vec2& vPos)
{
    float fWidth = GetWidth();
    float fHeight = GetHeight();
    m_vMin = vPos;
    m_vMax[0] = vPos[0] + fWidth;
    m_vMax[1] = vPos[1] + fHeight;
}

inline void O5Frame::Scale(const O5Vec2& vScale)
{
    SetWidth(GetWidth() * vScale[0]);
    SetHeight(GetHeight() * vScale[1]);
}

inline bool O5Frame::Intersect(const O5Vec2& vPoint) const
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

inline bool O5Frame::Overlap(const O5Frame& other) const
{
    O5Vec2 vDistance = other.Center() - Center();

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

inline O5Frame operator*(const O5Mat2& matrix, const O5Frame& frame)
{
    return O5Frame(frame[0] * matrix, frame[1] * matrix);
}

inline O5Frame operator*(const O5Frame& frame, const O5Mat2& matrix)
{
    return O5Frame(frame[0] * matrix, frame[1] * matrix);
}

inline O5Frame& O5Frame::operator*=(float fX)
{
    m_vMin *= fX;
    m_vMax *= fX;
    return *this;
}

inline O5Frame& O5Frame::operator*=(const O5Mat2& matrix)
{
    m_vMin *= matrix;
    m_vMax *= matrix;
    return *this;
}

inline O5Mat3x2 O5Frame::Orthographic() const
{
    return O5Mat3x2(O5Mat2(O5Vec2(2.0f / GetWidth(), 0.0f), O5Vec2(0.0f, 2.0f / (m_vMin[1] - m_vMax[1]))), O5Vec2((m_vMin[0] + m_vMax[0]) / (m_vMin[0] - m_vMax[0]), (m_vMin[1] + m_vMax[1]) / GetHeight()));
}
