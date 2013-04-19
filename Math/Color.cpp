//
// Copyright (c) 2012 On5. All rights reserved.
//

#include "Color.h"

namespace ftr {

ColorHSL ColorHSL::RGB2HSL(const Color4f& Color) const
{
    float fMax = Util::Maximum(Util::Maximum(Color.mR, Color.mG),Color.mB);
    float fMin = Util::Minimum(Util::Minimum(Color.mR, Color.mG),Color.mB);
    
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
    
    if(fMax == Color.mR)
    {
        return ColorHSL(((Color.mG-Color.mB)/fD + (Color.mG < Color.mB ? 6.0f : 0.0f))/6.0f, fS, fL);
    }
    
    if(fMax == Color.mG)
    {
        return ColorHSL(((Color.mB-Color.mR)/fD + 2.0f)/6.0f, fS, fL);
    }
    
    if(fMax == Color.mB)
    {
        return ColorHSL(((Color.mR-Color.mG)/fD + 4.0f)/6.0f, fS, fL);
    }
    
    return ColorHSL(fH,fS,fL);
}

Color4f ColorHSL::HSL2RGB(const ColorHSL& Color) const
{
    if(Color.mS == 0.0f)
    {
        return Color4f(Color.mL,Color.mL,Color.mL);
    }
    
    float fQ = Color.mL < 0.5 ? (Color.mL*(1.0f+Color.mS)) : (Color.mL+Color.mS-Color.mL*Color.mS);
    
    float fP = 2.0f * Color.mL - fQ;
    
    return Color4f(Hue2RGB(fP, fQ, Color.mH+1.0f/3.0f), Hue2RGB(fP, fQ, Color.mH), Hue2RGB(fP, fQ, Color.mH-1.0f/3.0f));
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
    float fMax = Util::Maximum(Util::Maximum(Color.mR, Color.mG),Color.mB);
    float fMin = Util::Minimum(Util::Minimum(Color.mR, Color.mG),Color.mB);
    
    if(fMax == fMin)
    {
        return ColorHSV(0.0f,fMax,fMax);
    }
    
    float fD = fMax - fMin;
    
    float fS = (fMax == 0.0f ? 0.0f : fD / fMax);
    
    float fH = fMax;
    float fV = fMax;
    
    if(fMax == Color.mR)
    {
        return ColorHSV((Color.mG - Color.mB)/fD + (Color.mG < Color.mB ? 6.0f : 0.0f)/6.0f,fS,fV);
    }
    
    if(fMax == Color.mG)
    {
        return ColorHSV(((Color.mB - Color.mR)/fD + 2.0f)/6.0f,fS,fV);
    }
    
    if(fMax == Color.mR)
    {
        return ColorHSV(((Color.mR-Color.mG)/fD + 4.0f)/6.0f,fS,fV);
    }
    
    return ColorHSV(fH,fS,fV);
}

Color4f ColorHSV::HSV2RGB(const ColorHSV& Color) const
{
    float fR = 0.0f;
    float fG = 0.0f;
    float fB = 0.0f;
    
    Byte bIndex = floorf(Color.mH*6.0f);
    
    float fF = Color.mH * 6.0f - bIndex;
    float fP = Color.mV * (1.0f - Color.mS);
    float fQ = Color.mV * (1.0f - fF * Color.mS);
    float fT = Color.mV * (1.0f - (1.0f - fF) * Color.mS);
    
    switch(bIndex%6)
    {
        case 0:{fR = Color.mV; fG = fT; fB = fP;} break;
        case 1:{fR = fQ; fG = Color.mV; fB = fP;} break;
        case 2:{fR = fP; fG = Color.mV; fB = fT;} break;
        case 3:{fR = fP; fG = fQ; fB = Color.mV;} break;
        case 4:{fR = fT; fG = fP; fB = Color.mV;} break;
        case 5:{fR = Color.mV; fG = fP; fB = fQ;} break;
    }
    
    return Color4f(fR, fG, fB);
}

}