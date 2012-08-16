//
// Copyright (c) 2012 On5. All rights reserved.
//

const float O5Epsilon = 1.19209e-07f;
const float O5Pi = 3.14159265f;

inline bool O5Approximately(float a, float b)
{
    return std::abs(a - b) < O5Epsilon;
}

inline bool O5PowerOfTwo(unsigned int n)
{
	return n && !(n & (n - 1));
}

inline float O5Lerp(float x, float y, float t)
{
    return x + t * (y - x);
}

inline float O5Clamp(float fValue, float fMin, float fMax)
{
    return ( fValue < fMin ? fMin : (fValue > fMax ? fMax : fValue) );
}

inline float O5Maximum(float fA, float fB)
{
    return (fA > fB ? fA : fB);
}

inline float O5Minimum(float fA, float fB)
{
    return (fA < fB ? fA : fB);
}

inline int O5Maximum(int iA, int iB)
{
    return (iA > iB ? iA : iB);
}

inline int O5Minimum(int iA, int iB)
{
    return (iA < iB ? iA : iB);
}

inline float O5Sign(float fValue)
{
    return (fValue < 0.0f) ? -1.0f : ((fValue > 0.0f) ? 1.0f : 0.0f);
}

inline int O5HighestPowerOfTwo(int n)
{
    if(O5PowerOfTwo(n)) 
    {
        return n;
    }

    int i = 1;

    while(i < n)
    {
        i <<= 1;
    }

    return i;
}

inline int O5NearestPowerOfTwo(int n)
{
    int i = O5HighestPowerOfTwo(n);
    int j = i >> 1;

    if(i - n < n - j)
        return i;
    else
        return j;
}

inline float O5Bezier(float a, float b, float c, float d, float t)
{
    return a + t * t * t * (d + 3.0f * (b - c) - a) + 3.0f * t * t * (a - 2.0f * b + c) + 3.0f * t * (b - a);
}
    
inline float O5Random(float a, float b)
{
    return O5Lerp(a, b, static_cast<float>(std::rand() % RAND_MAX) / static_cast<float>(RAND_MAX));
}

inline float O5Ease(float fA, float fB, float fValue)
{
	return O5Lerp(fA, fB, ((6.0f * fValue - 15.0f) * fValue + 10.0f) * fValue * fValue * fValue);
}

inline float O5Radian(float fDegree)
{
    return (fDegree/180.0f)*O5Pi;
}

inline float O5Degree(float fRadian)
{
    return (fRadian/O5Pi)*180.0f;
}
