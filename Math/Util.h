//
// Copyright (c) 2012 On5. All rights reserved.
//

#pragma once

namespace Factory { namespace Util {

const float Epsilon = 1.19209e-07f;
const float Pi = 3.14159265f;

inline bool Approximately(float a, float b)
{
    return std::abs(a - b) < Epsilon;
}

inline bool PowerOfTwo(unsigned int n)
{
	return n && !(n & (n - 1));
}

inline float Lerp(float x, float y, float t)
{
    return x + t * (y - x);
}

inline float Clamp(float fValue, float fMin, float fMax)
{
    return ( fValue < fMin ? fMin : (fValue > fMax ? fMax : fValue) );
}

inline float Maximum(float fA, float fB)
{
    return (fA > fB ? fA : fB);
}

inline float Minimum(float fA, float fB)
{
    return (fA < fB ? fA : fB);
}

inline int Maximum(int iA, int iB)
{
    return (iA > iB ? iA : iB);
}

inline int Minimum(int iA, int iB)
{
    return (iA < iB ? iA : iB);
}

inline float Sign(float fValue)
{
    return (fValue < 0.0f) ? -1.0f : ((fValue > 0.0f) ? 1.0f : 0.0f);
}

inline int HighestPowerOfTwo(int n)
{
    if(PowerOfTwo(n)) 
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

inline int NearestPowerOfTwo(int n)
{
    int i = HighestPowerOfTwo(n);
    int j = i >> 1;

    if(i - n < n - j)
        return i;
    else
        return j;
}

inline float Bezier(float a, float b, float c, float d, float t)
{
    return a + t * t * t * (d + 3.0f * (b - c) - a) + 3.0f * t * t * (a - 2.0f * b + c) + 3.0f * t * (b - a);
}
    
inline float Random(float a, float b)
{
    return Lerp(a, b, static_cast<float>(std::rand() % RAND_MAX) / static_cast<float>(RAND_MAX));
}

inline float Ease(float fA, float fB, float fValue)
{
	return Lerp(fA, fB, ((6.0f * fValue - 15.0f) * fValue + 10.0f) * fValue * fValue * fValue);
}

inline float Radian(float fDegree)
{
    return (fDegree/180.0f)*Pi;
}

inline float Degree(float fRadian)
{
    return (fRadian/Pi)*180.0f;
}
    
}}