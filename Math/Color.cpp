//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Color.h"

namespace ftr {

ColorHSL ColorHSL::RGB2HSL(const Color4f& Color) const
{
    float fMax = Util::Maximum(Util::Maximum(Color.m_fR, Color.m_fG),Color.m_fB);
    float fMin = Util::Minimum(Util::Minimum(Color.m_fR, Color.m_fG),Color.m_fB);
    
    if(fMax == fMin)
    {
        return ColorHSL(0.0f,0.0f,(fMax+fMin)/2.0f);
    }
    
    float fAverage = (fMax+fMin)/2.0f;
    
    float fH = fAverage;
    float fS = fAverage;
    float fL = fAverage;
    
    float fD = fMax - fMin;
    
    fS = fL > 0.5f ? (fD/(2.0f-fMax-fMin)) : (fD/(fMax+fMin));
    
    if(fMax == Color.m_fR)
    {
        return ColorHSL(((Color.m_fG-Color.m_fB)/fD + (Color.m_fG < Color.m_fB ? 6.0f : 0.0f))/6.0f, fS, fL);
    }
    
    if(fMax == Color.m_fG)
    {
        return ColorHSL(((Color.m_fB-Color.m_fR)/fD + 2.0f)/6.0f, fS, fL);
    }
    
    if(fMax == Color.m_fB)
    {
        return ColorHSL(((Color.m_fR-Color.m_fG)/fD + 4.0f)/6.0f, fS, fL);
    }
    
    return ColorHSL(fH,fS,fL);
}

Color4f ColorHSL::HSL2RGB(const ColorHSL& Color) const
{
    if(Color.m_fS == 0.0f)
    {
        return Color4f(Color.m_fL,Color.m_fL,Color.m_fL);
    }
    
    float fQ = Color.m_fL < 0.5 ? (Color.m_fL*(1.0f+Color.m_fS)) : (Color.m_fL+Color.m_fS-Color.m_fL*Color.m_fS);
    
    float fP = 2.0f * Color.m_fL - fQ;
    
    return Color4f(Hue2RGB(fP, fQ, Color.m_fH+1.0f/3.0f), Hue2RGB(fP, fQ, Color.m_fH), Hue2RGB(fP, fQ, Color.m_fH-1.0f/3.0f));
}

float ColorHSL::Hue2RGB(float fP, float fQ, float fT) const
{
    if(fT < 0.0f) fT += 1.0f;
    if(fT > 1.0f) fT -= 1.0f;
    
    if(fT < 1.0f/6.0f) return (fP + (fQ - fP) * 6.0f * fT);
    if(fT < 1.0f/2.0f) return fQ;
    if(fT < 2.0f/3.0f) return (fP + (fQ - fP) * (2.0f/3.0f - fT) * 6.0f);
    
    return fP;
}

ColorHSV ColorHSV::RGB2HSV(const Color4f &Color) const
{
    float fMax = Util::Maximum(Util::Maximum(Color.m_fR, Color.m_fG),Color.m_fB);
    float fMin = Util::Minimum(Util::Minimum(Color.m_fR, Color.m_fG),Color.m_fB);
    
    if(fMax == fMin)
    {
        return ColorHSV(0.0f,fMax,fMax);
    }
    
    float fD = fMax - fMin;
    
    float fS = (fMax == 0.0f ? 0.0f : fD / fMax);
    
    float fH = fMax;
    float fV = fMax;
    
    if(fMax == Color.m_fR)
    {
        return ColorHSV((Color.m_fG - Color.m_fB)/fD + (Color.m_fG < Color.m_fB ? 6.0f : 0.0f)/6.0f,fS,fV);
    }
    
    if(fMax == Color.m_fG)
    {
        return ColorHSV(((Color.m_fB - Color.m_fR)/fD + 2.0f)/6.0f,fS,fV);
    }
    
    if(fMax == Color.m_fR)
    {
        return ColorHSV(((Color.m_fR-Color.m_fG)/fD + 4.0f)/6.0f,fS,fV);
    }
    
    return ColorHSV(fH,fS,fV);
}

Color4f ColorHSV::HSV2RGB(const ColorHSV& Color) const
{
    float fR = 0.0f;
    float fG = 0.0f;
    float fB = 0.0f;
    
    Byte bIndex = floorf(Color.m_fH*6.0f);
    
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
    
    return Color4f(fR, fG, fB);
}

}