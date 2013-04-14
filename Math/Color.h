//
// Copyright (c) 2012 On5. All rights reserved.
//

#pragma once

namespace Factory {

class _ALIGN(16) Color4f
{
public:
    float           m_fR;
    float           m_fG;
    float           m_fB;
    float           m_fA;

    explicit        Color4f(float fR = 0.0f, float fG = 0.0f, float fB = 0.0f, float fA = 1.0f): m_fR(fR), m_fG(fG), m_fB(fB), m_fA(fA) {}
                    Color4f(Byte bR, Byte bG, Byte bB, Byte bA = 255) {Set(bR, bG, bB, bA);}
                    Color4f(const Color4f& other): m_fR(other.m_fR), m_fG(other.m_fG), m_fB(other.m_fB), m_fA(other.m_fA) {}
    explicit        Color4f(const class Color4b& other);

    Color4f&      operator=(const Color4f& other) {Set(other.m_fR, other.m_fG, other.m_fB, other.m_fA); return *this;}
    Color4f&      operator=(const class Color4b& other);
    float&          operator[](int index) {return (&m_fR)[index];}
    float           operator[](int index) const {return (&m_fR)[index];}
    Color4f       operator*(float fValue) const {return Color4f(m_fR * fValue, m_fG * fValue, m_fB * fValue, m_fA * fValue);}

    void            Set(float fR, float fG, float fB, float fA = 1.0f) {m_fR = fR; m_fG = fG; m_fB = fB; m_fA = fA;}
    void            Set(Byte bR, Byte bG, Byte bB, Byte bA = 255);
    float*          Pointer() {return &m_fR;}
    const float*    Pointer() const {return &m_fR;}
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
    m_fR = static_cast<float>(bR) * 0.003921568627451f;
    m_fG = static_cast<float>(bG) * 0.003921568627451f;
    m_fB = static_cast<float>(bB) * 0.003921568627451f;
    m_fA = static_cast<float>(bA) * 0.003921568627451f;
}

inline Color4b::Color4b(const Color4f& other)
{
    Set(other.m_fR, other.m_fG, other.m_fB, other.m_fA);
}

inline Color4b& Color4b::operator=(const Color4f& other)
{
    Set(other.m_fR, other.m_fG, other.m_fB, other.m_fA);
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
                    ColorHSL(): m_fH(0.0f), m_fS(0.0f), m_fL(0.0f) {};
                    ColorHSL(float fH, float fS, float fL) : m_fH(fH), m_fS(fS), m_fL(fL) {};
    
    ColorHSL      RGB2HSL(const Color4f& Color) const;
    ColorHSL      RGB2HSL(const Color4b& Color) const;
    ColorHSL      RGB2HSL(float fR, float fG, float fB) const;
    ColorHSL      RGB2HSL(Byte bR, Byte bG, Byte bB) const;
    
    Color4f       HSL2RGB() const;
    Color4f       HSL2RGB(const ColorHSL& Color) const;
    Color4f       HSL2RGB(float fH, float fS, float fL) const;
 
    float&          operator[](Byte bIndex) {return (&m_fH)[bIndex];}
    float           operator[](Byte bIndex) const {return (&m_fH)[bIndex];}
 
    float*          Pointer() {return &m_fH;}
    const float*    Pointer() const {return &m_fH;}
    
    float           Hue2RGB(float fP, float fQ, float fT) const;

    float           m_fH;
    float           m_fS;
    float           m_fL;
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
                    ColorHSV() : m_fH(0.0f),m_fS(0.0f),m_fV(0.0) {};
                    ColorHSV(float fH, float fS, float fV) : m_fH(fH), m_fS(fS), m_fV(fV) {};
    
    ColorHSV      RGB2HSV(const Color4f& Color) const;
    ColorHSV      RGB2HSV(const Color4b& Color) const;
    ColorHSV      RGB2HSV(float fR, float fG, float fB) const;
    ColorHSV      RGB2HSV(Byte bR, Byte bG, Byte bB) const;
    
    Color4f       HSV2RGB() const;
    Color4f       HSV2RGB(const ColorHSV& Color) const;
    Color4f       HSV2RGB(float fH, float fS, float fV) const;
    
    float&          operator[](Byte bIndex) {return (&m_fH)[bIndex];}
    float           operator[](Byte bIndex) const {return (&m_fH)[bIndex];}

    float*          Pointer() {return &m_fH;}
    const float*    Pointer() const {return &m_fH;}
    
    float           m_fH;
    float           m_fS;
    float           m_fV;
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