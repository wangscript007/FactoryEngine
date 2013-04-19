//
// Copyright (c) 2012 On5. All rights reserved.
//

#pragma once

namespace ftr {

class _ALIGN(16) Color4f
{
public:
    float           mR;
    float           mG;
    float           mB;
    float           mA;

    explicit        Color4f(float fR = 0.0f, float fG = 0.0f, float fB = 0.0f, float fA = 1.0f): mR(fR), mG(fG), mB(fB), mA(fA) {}
                    Color4f(Byte bR, Byte bG, Byte bB, Byte bA = 255) {Set(bR, bG, bB, bA);}
                    Color4f(const Color4f& other): mR(other.mR), mG(other.mG), mB(other.mB), mA(other.mA) {}
    explicit        Color4f(const class Color4b& other);

    Color4f&      operator=(const Color4f& other) {Set(other.mR, other.mG, other.mB, other.mA); return *this;}
    Color4f&      operator=(const class Color4b& other);
    float&          operator[](int index) {return (&mR)[index];}
    float           operator[](int index) const {return (&mR)[index];}
    Color4f       operator*(float fValue) const {return Color4f(mR * fValue, mG * fValue, mB * fValue, mA * fValue);}

    void            Set(float fR, float fG, float fB, float fA = 1.0f) {mR = fR; mG = fG; mB = fB; mA = fA;}
    void            Set(Byte bR, Byte bG, Byte bB, Byte bA = 255);
    float*          Pointer() {return &mR;}
    const float*    Pointer() const {return &mR;}
};

class _ALIGN(4) Color4b
{
public:
    Byte          m_bR;
    Byte          m_bG;
    Byte          m_bB;
    Byte          m_bA;

                    Color4b(float fR, float fG, float fB, float fA = 1.0f) {Set(fR, fG, fB, fA);}
    explicit        Color4b(Byte bR = 0, Byte bG = 0, Byte bB = 0, Byte bA = 255) {Set(bR, bG, bB, bA);}
                    Color4b(const Color4b& other): m_bR(other.m_bR), m_bG(other.m_bG), m_bB(other.m_bB), m_bA(other.m_bA) {}
    explicit        Color4b(const Color4f& other);

    Color4b&      operator=(const Color4f& other);
    Color4b&      operator=(const Color4b& other) {Set(other.m_bR, other.m_bG, other.m_bB, other.m_bA); return *this;}
    Byte&         operator[](int index) {return (&m_bR)[index];}
    Byte          operator[](int index) const {return (&m_bR)[index];}

    void            Set(float fR, float fG, float fB, float fA = 1.0f);
    void            Set(Byte bR, Byte bG, Byte bB, Byte bA = 255) {m_bR = bR; m_bG = bG; m_bB = bB; m_bA = bA;}
    Byte*         Pointer() {return &m_bR;}
    const Byte*   Pointer() const {return &m_bR;}
};

inline Color4f::Color4f(const Color4b& other)
{
    Set(other.m_bR, other.m_bG, other.m_bB, other.m_bA);
}

inline Color4f& Color4f::operator=(const Color4b& other)
{
    Set(other.m_bR, other.m_bG, other.m_bB, other.m_bA);
    return *this;
}

inline void Color4f::Set(Byte bR, Byte bG, Byte bB, Byte bA)
{
    mR = static_cast<float>(bR) * 0.003921568627451f;
    mG = static_cast<float>(bG) * 0.003921568627451f;
    mB = static_cast<float>(bB) * 0.003921568627451f;
    mA = static_cast<float>(bA) * 0.003921568627451f;
}

inline Color4b::Color4b(const Color4f& other)
{
    Set(other.mR, other.mG, other.mB, other.mA);
}

inline Color4b& Color4b::operator=(const Color4f& other)
{
    Set(other.mR, other.mG, other.mB, other.mA);
    return *this;
}

inline void Color4b::Set(float fR, float fG, float fB, float fA)
{
    m_bR = static_cast<Byte>(fR * 255.0f);
    m_bG = static_cast<Byte>(fG * 255.0f);
    m_bB = static_cast<Byte>(fB * 255.0f);
    m_bA = static_cast<Byte>(fA * 255.0f);
}

class ColorHSL
{
public:
                    ColorHSL(): mH(0.0f), mS(0.0f), mL(0.0f) {};
                    ColorHSL(float fH, float fS, float fL) : mH(fH), mS(fS), mL(fL) {};
    
    ColorHSL      RGB2HSL(const Color4f& Color) const;
    ColorHSL      RGB2HSL(const Color4b& Color) const;
    ColorHSL      RGB2HSL(float fR, float fG, float fB) const;
    ColorHSL      RGB2HSL(Byte bR, Byte bG, Byte bB) const;
    
    Color4f       HSL2RGB() const;
    Color4f       HSL2RGB(const ColorHSL& Color) const;
    Color4f       HSL2RGB(float fH, float fS, float fL) const;
 
    float&          operator[](Byte bIndex) {return (&mH)[bIndex];}
    float           operator[](Byte bIndex) const {return (&mH)[bIndex];}
 
    float*          Pointer() {return &mH;}
    const float*    Pointer() const {return &mH;}
    
    float           Hue2RGB(float fP, float fQ, float fT) const;

    float           mH;
    float           mS;
    float           mL;
};

inline ColorHSL ColorHSL::RGB2HSL(const Color4b &Color) const
{
    return RGB2HSL(Color4f(Color));
}

inline ColorHSL ColorHSL::RGB2HSL(float fR, float fG, float fB) const
{
    return RGB2HSL(Color4f(fR, fG, fB));
}

inline ColorHSL ColorHSL::RGB2HSL(Byte bR, Byte bG, Byte bB) const
{
    return RGB2HSL(Color4f(bR, bG, bB));
}

inline Color4f ColorHSL::HSL2RGB(float fH, float fS, float fL) const
{
    return HSL2RGB(ColorHSL(fH,fS,fL));
}

inline Color4f ColorHSL::HSL2RGB() const
{
    return HSL2RGB(*this);
}

class ColorHSV
{
public:
                    ColorHSV() : mH(0.0f),mS(0.0f),mV(0.0) {};
                    ColorHSV(float fH, float fS, float fV) : mH(fH), mS(fS), mV(fV) {};
    
    ColorHSV      RGB2HSV(const Color4f& Color) const;
    ColorHSV      RGB2HSV(const Color4b& Color) const;
    ColorHSV      RGB2HSV(float fR, float fG, float fB) const;
    ColorHSV      RGB2HSV(Byte bR, Byte bG, Byte bB) const;
    
    Color4f       HSV2RGB() const;
    Color4f       HSV2RGB(const ColorHSV& Color) const;
    Color4f       HSV2RGB(float fH, float fS, float fV) const;
    
    float&          operator[](Byte bIndex) {return (&mH)[bIndex];}
    float           operator[](Byte bIndex) const {return (&mH)[bIndex];}

    float*          Pointer() {return &mH;}
    const float*    Pointer() const {return &mH;}
    
    float           mH;
    float           mS;
    float           mV;
};

inline ColorHSV ColorHSV::RGB2HSV(const Color4b& Color) const
{
    return RGB2HSV(Color4f(Color));
}

inline ColorHSV ColorHSV::RGB2HSV(float fR, float fG, float fB) const
{
    return RGB2HSV(Color4b(fR, fG, fB));
}

inline ColorHSV ColorHSV::RGB2HSV(Byte bR, Byte bG, Byte bB) const
{
    return RGB2HSV(Color4f(bR, bG, bB));
}

inline Color4f ColorHSV::HSV2RGB(float fH, float fS, float fV) const
{
    return HSV2RGB(ColorHSV(fH,fS,fV));
}

inline Color4f ColorHSV::HSV2RGB() const
{
    return HSV2RGB(*this);
}

}