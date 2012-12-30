//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Color.h"

O5ColorHSL O5ColorHSL::RGB2HSL(const O5Color4f& Color) const
{
    float fMax = O5Maximum(O5Maximum(Color.m_fR, Color.m_fG),Color.m_fB);
    float fMin = O5Minimum(O5Minimum(Color.m_fR, Color.m_fG),Color.m_fB);
    
    if(fMax == fMin)
    {
        return O5ColorHSL(0.0f,0.0f,(fMax+fMin)/2.0f);
    }
    
    float fAverage = (fMax+fMin)/2.0f;
    
    float fH = fAverage;
    float fS = fAverage;
    float fL = fAverage;
    
    float fD = fMax - fMin;
    
    fS = fL > 0.5f ? (fD/(2.0f-fMax-fMin)) : (fD/(fMax+fMin));
    
    if(fMax == Color.m_fR)
    {
        return O5ColorHSL(((Color.m_fG-Color.m_fB)/fD + (Color.m_fG < Color.m_fB ? 6.0f : 0.0f))/6.0f, fS, fL);
    }
    
    if(fMax == Color.m_fG)
    {
        return O5ColorHSL(((Color.m_fB-Color.m_fR)/fD + 2.0f)/6.0f, fS, fL);
    }
    
    if(fMax == Color.m_fB)
    {
        return O5ColorHSL(((Color.m_fR-Color.m_fG)/fD + 4.0f)/6.0f, fS, fL);
    }
    
    return O5ColorHSL(fH,fS,fL);
}

O5Color4f O5ColorHSL::HSL2RGB(const O5ColorHSL& Color) const
{
    if(Color.m_fS == 0.0f)
    {
        return O5Color4f(Color.m_fL,Color.m_fL,Color.m_fL);
    }
    
    float fQ = Color.m_fL < 0.5 ? (Color.m_fL*(1.0f+Color.m_fS)) : (Color.m_fL+Color.m_fS-Color.m_fL*Color.m_fS);
    
    float fP = 2.0f * Color.m_fL - fQ;
    
    return O5Color4f(Hue2RGB(fP, fQ, Color.m_fH+1.0f/3.0f), Hue2RGB(fP, fQ, Color.m_fH), Hue2RGB(fP, fQ, Color.m_fH-1.0f/3.0f));
}

float O5ColorHSL::Hue2RGB(float fP, float fQ, float fT) const
{
    if(fT < 0.0f) fT += 1.0f;
    if(fT > 1.0f) fT -= 1.0f;
    
    if(fT < 1.0f/6.0f) return (fP + (fQ - fP) * 6.0f * fT);
    if(fT < 1.0f/2.0f) return fQ;
    if(fT < 2.0f/3.0f) return (fP + (fQ - fP) * (2.0f/3.0f - fT) * 6.0f);
    
    return fP;
}

O5ColorHSV O5ColorHSV::RGB2HSV(const O5Color4f &Color) const
{
    float fMax = O5Maximum(O5Maximum(Color.m_fR, Color.m_fG),Color.m_fB);
    float fMin = O5Minimum(O5Minimum(Color.m_fR, Color.m_fG),Color.m_fB);
    
    if(fMax == fMin)
    {
        return O5ColorHSV(0.0f,fMax,fMax);
    }
    
    float fD = fMax - fMin;
    
    float fS = (fMax == 0.0f ? 0.0f : fD / fMax);
    
    float fH = fMax;
    float fV = fMax;
    
    if(fMax == Color.m_fR)
    {
        return O5ColorHSV((Color.m_fG - Color.m_fB)/fD + (Color.m_fG < Color.m_fB ? 6.0f : 0.0f)/6.0f,fS,fV);
    }
    
    if(fMax == Color.m_fG)
    {
        return O5ColorHSV(((Color.m_fB - Color.m_fR)/fD + 2.0f)/6.0f,fS,fV);
    }
    
    if(fMax == Color.m_fR)
    {
        return O5ColorHSV(((Color.m_fR-Color.m_fG)/fD + 4.0f)/6.0f,fS,fV);
    }
    
    return O5ColorHSV(fH,fS,fV);
}

O5Color4f O5ColorHSV::HSV2RGB(const O5ColorHSV& Color) const
{
    float fR = 0.0f;
    float fG = 0.0f;
    float fB = 0.0f;
    
    O5Byte bIndex = floorf(Color.m_fH*6.0f);
    
    float fF = Color.m_fH * 6.0f - bIndex;
    float fP = Color.m_fV * (1.0f - Color.m_fS);
    float fQ = Color.m_fV * (1.0f - fF * Color.m_fS);
    float fT = Color.m_fV * (1.0f - (1.0f - fF) * Color.m_fS);
    
    switch(bIndex%6)
    {
        case 0:{fR = Color.m_fV; fG = fT; fB = fP;} break;
        case 1:{fR = fQ; fG = Color.m_fV; fB = fP;} break;
        case 2:{fR = fP; fG = Color.m_fV; fB = fT;} break;
        case 3:{fR = fP; fG = fQ; fB = Color.m_fV;} break;
        case 4:{fR = fT; fG = fP; fB = Color.m_fV;} break;
        case 5:{fR = Color.m_fV; fG = fP; fB = fQ;} break;
    }
    
    return O5Color4f(fR, fG, fB);
}