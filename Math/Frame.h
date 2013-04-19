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
    Vec2          mMin;
    Vec2          mMax;

                    Frame() {}
                    Frame(const Frame& other): mMin(other.mMin), mMax(other.mMax) {}
                    Frame(const Vec2& min, const Vec2& max): mMin(min), mMax(max) {}

    Frame         operator-(const Vec2& pos) const {return Frame(mMin - pos, mMax - pos);}
    Frame         operator+(const Vec2& pos) const {return Frame(mMin + pos, mMax + pos);}
    Frame&        operator+=(const Vec2& pos);
    Frame&        operator-=(const Vec2& pos);
    Frame&        operator=(const Frame& other);
    Frame&        operator*=(const Mat2& matrix);
    Frame         operator*(float x) const {return Frame(mMin * x, mMax * x);}
    Frame&        operator*=(float x);
    Vec2&         operator[](int index) {return (&mMin)[index];}
    const Vec2&   operator[](int index) const {return (&mMin)[index];}
    bool            operator==(const Frame& other) const {return mMin == other.mMin && mMax == other.mMax;}
    bool            operator!=(const Frame& other) const {return mMin != other.mMin || mMax != other.mMax;}

    void            set(const Vec2& min, const Vec2& max);
    float           GetWidth() const {return mMax.mX - mMin.mX;}
    float           GetHeight() const {return mMax.mY - mMin.mY;}
    void            setWidth(float width) {mMax.mX = mMin.mX + width;}
    void            setHeight(float fHeight) {mMax.mY = mMin.mY + fHeight;}
    void            setPosition(const Vec2& pos);
    void            Scale(const Vec2& scale);
    const Vec2&   GetPosition() const {return mMin;}
    void            setExtent(const Vec2& extent);
    Vec2          GetExtent() const {return Vec2(GetWidth(), GetHeight());}
    bool            Intersect(const Vec2& point) const;
    bool            Intersect(const Frame& other) const {return Intersect(other[0]) && Intersect(other[1]);}
    bool            Overlap(const Frame& other) const;
    Vec2          Center() const {return (mMin + mMax) * 0.5f;}
    Mat3x2        Orthographic() const;
};

inline Frame& Frame::operator=(const Frame& other)
{
    mMin = other.mMin;
    mMax = other.mMax;
    return *this;
}

inline Frame& Frame::operator-=(const Vec2& pos)
{
    mMin -= pos;
    mMax -= pos;
    return *this;
}

inline Frame& Frame::operator+=(const Vec2& pos)
{
    mMin += pos;
    mMax += pos;
    return *this;
}

inline void Frame::set(const Vec2& min, const Vec2& max)
{
    mMin = min;
    mMax = max;
}

inline void Frame::setExtent(const Vec2& extent)
{
    setWidth(extent[0]);
    setHeight(extent[1]);
}

inline void Frame::setPosition(const Vec2& pos)
{
    float width = GetWidth();
    float fHeight = GetHeight();
    mMin = pos;
    mMax[0] = pos[0] + width;
    mMax[1] = pos[1] + fHeight;
}

inline void Frame::Scale(const Vec2& scale)
{
    setWidth(GetWidth() * scale[0]);
    setHeight(GetHeight() * scale[1]);
}

inline bool Frame::Intersect(const Vec2& point) const
{
    if(point[0] < mMin[0])
    {
        return false;
    }
    if(point[1] < mMin[1])
    {
        return false;
    }
    if(point[0] > mMax[0])
    {
        return false;
    }
    if(point[1] > mMax[1])
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

inline Frame& Frame::operator*=(float x)
{
    mMin *= x;
    mMax *= x;
    return *this;
}

inline Frame& Frame::operator*=(const Mat2& matrix)
{
    mMin *= matrix;
    mMax *= matrix;
    return *this;
}

inline Mat3x2 Frame::Orthographic() const
{
    return Mat3x2(Mat2(Vec2(2.0f / GetWidth(), 0.0f), Vec2(0.0f, 2.0f / (mMin[1] - mMax[1]))), Vec2((mMin[0] + mMax[0]) / (mMin[0] - mMax[0]), (mMin[1] + mMax[1]) / GetHeight()));
}

}