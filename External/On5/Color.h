//
// Copyright (c) 2012 On5. All rights reserved.
//

class O5_ALIGN(16) O5Color4f
{
public:
    float           m_fR;
    float           m_fG;
    float           m_fB;
    float           m_fA;

    explicit        O5Color4f(float fR = 0.0f, float fG = 0.0f, float fB = 0.0f, float fA = 1.0f): m_fR(fR), m_fG(fG), m_fB(fB), m_fA(fA) {}
                    O5Color4f(O5Byte bR, O5Byte bG, O5Byte bB, O5Byte bA = 255) {Set(bR, bG, bB, bA);}
                    O5Color4f(const O5Color4f& other): m_fR(other.m_fR), m_fG(other.m_fG), m_fB(other.m_fB), m_fA(other.m_fA) {}
    explicit        O5Color4f(const class O5Color4b& other);

    O5Color4f&      operator=(const O5Color4f& other) {Set(other.m_fR, other.m_fG, other.m_fB, other.m_fA); return *this;}
    O5Color4f&      operator=(const class O5Color4b& other);
    float&          operator[](int index) {return (&m_fR)[index];}
    float           operator[](int index) const {return (&m_fR)[index];}
    O5Color4f       operator*(float fValue) const {return O5Color4f(m_fR * fValue, m_fG * fValue, m_fB * fValue, m_fA * fValue);}

    void            Set(float fR, float fG, float fB, float fA = 1.0f) {m_fR = fR; m_fG = fG; m_fB = fB; m_fA = fA;}
    void            Set(O5Byte bR, O5Byte bG, O5Byte bB, O5Byte bA = 255);
    float*          Pointer() {return &m_fR;}
    const float*    Pointer() const {return &m_fR;}
};

class O5_ALIGN(4) O5Color4b
{
public:
    O5Byte          m_bR;
    O5Byte          m_bG;
    O5Byte          m_bB;
    O5Byte          m_bA;

                    O5Color4b(float fR, float fG, float fB, float fA = 1.0f) {Set(fR, fG, fB, fA);}
    explicit        O5Color4b(O5Byte bR = 0, O5Byte bG = 0, O5Byte bB = 0, O5Byte bA = 255) {Set(bR, bG, bB, bA);}
                    O5Color4b(const O5Color4b& other): m_bR(other.m_bR), m_bG(other.m_bG), m_bB(other.m_bB), m_bA(other.m_bA) {}
    explicit        O5Color4b(const O5Color4f& other);

    O5Color4b&      operator=(const O5Color4f& other);
    O5Color4b&      operator=(const O5Color4b& other) {Set(other.m_bR, other.m_bG, other.m_bB, other.m_bA); return *this;}
    O5Byte&         operator[](int index) {return (&m_bR)[index];}
    O5Byte          operator[](int index) const {return (&m_bR)[index];}

    void            Set(float fR, float fG, float fB, float fA = 1.0f);
    void            Set(O5Byte bR, O5Byte bG, O5Byte bB, O5Byte bA = 255) {m_bR = bR; m_bG = bG; m_bB = bB; m_bA = bA;}
    O5Byte*         Pointer() {return &m_bR;}
    const O5Byte*   Pointer() const {return &m_bR;}
};

inline O5Color4f::O5Color4f(const O5Color4b& other)
{
    Set(other.m_bR, other.m_bG, other.m_bB, other.m_bA);
}

inline O5Color4f& O5Color4f::operator=(const O5Color4b& other)
{
    Set(other.m_bR, other.m_bG, other.m_bB, other.m_bA);
    return *this;
}

inline void O5Color4f::Set(O5Byte bR, O5Byte bG, O5Byte bB, O5Byte bA)
{
    m_fR = static_cast<float>(bR) * 0.003921568627451f;
    m_fG = static_cast<float>(bG) * 0.003921568627451f;
    m_fB = static_cast<float>(bB) * 0.003921568627451f;
    m_fA = static_cast<float>(bA) * 0.003921568627451f;
}

inline O5Color4b::O5Color4b(const O5Color4f& other)
{
    Set(other.m_fR, other.m_fG, other.m_fB, other.m_fA);
}

inline O5Color4b& O5Color4b::operator=(const O5Color4f& other)
{
    Set(other.m_fR, other.m_fG, other.m_fB, other.m_fA);
    return *this;
}

inline void O5Color4b::Set(float fR, float fG, float fB, float fA)
{
    m_bR = static_cast<O5Byte>(fR * 255.0f);
    m_bG = static_cast<O5Byte>(fG * 255.0f);
    m_bB = static_cast<O5Byte>(fB * 255.0f);
    m_bA = static_cast<O5Byte>(fA * 255.0f);
}

class O5ColorHSL
{
public:
                    O5ColorHSL(): m_fH(0.0f), m_fS(0.0f), m_fL(0.0f) {};
                    O5ColorHSL(float fH, float fS, float fL) : m_fH(fH), m_fS(fS), m_fL(fL) {};
    
    O5ColorHSL      RGB2HSL(const O5Color4f& Color) const;
    O5ColorHSL      RGB2HSL(const O5Color4b& Color) const;
    O5ColorHSL      RGB2HSL(float fR, float fG, float fB) const;
    O5ColorHSL      RGB2HSL(O5Byte bR, O5Byte bG, O5Byte bB) const;
    
    O5Color4f       HSL2RGB() const;
    O5Color4f       HSL2RGB(const O5ColorHSL& Color) const;
    O5Color4f       HSL2RGB(float fH, float fS, float fL) const;
 
    float&          operator[](O5Byte bIndex) {return (&m_fH)[bIndex];}
    float           operator[](O5Byte bIndex) const {return (&m_fH)[bIndex];}
 
    float*          Pointer() {return &m_fH;}
    const float*    Pointer() const {return &m_fH;}
    
    float           Hue2RGB(float fP, float fQ, float fT) const;

    float           m_fH;
    float           m_fS;
    float           m_fL;
};

inline O5ColorHSL O5ColorHSL::RGB2HSL(const O5Color4b &Color) const
{
    return RGB2HSL(O5Color4f(Color));
}

inline O5ColorHSL O5ColorHSL::RGB2HSL(float fR, float fG, float fB) const
{
    return RGB2HSL(O5Color4f(fR, fG, fB));
}

inline O5ColorHSL O5ColorHSL::RGB2HSL(O5Byte bR, O5Byte bG, O5Byte bB) const
{
    return RGB2HSL(O5Color4f(bR, bG, bB));
}

inline O5Color4f O5ColorHSL::HSL2RGB(float fH, float fS, float fL) const
{
    return HSL2RGB(O5ColorHSL(fH,fS,fL));
}

inline O5Color4f O5ColorHSL::HSL2RGB() const
{
    return HSL2RGB(*this);
}

class O5ColorHSV
{
public:
                    O5ColorHSV() : m_fH(0.0f),m_fS(0.0f),m_fV(0.0) {};
                    O5ColorHSV(float fH, float fS, float fV) : m_fH(fH), m_fS(fS), m_fV(fV) {};
    
    O5ColorHSV      RGB2HSV(const O5Color4f& Color) const;
    O5ColorHSV      RGB2HSV(const O5Color4b& Color) const;
    O5ColorHSV      RGB2HSV(float fR, float fG, float fB) const;
    O5ColorHSV      RGB2HSV(O5Byte bR, O5Byte bG, O5Byte bB) const;
    
    O5Color4f       HSV2RGB() const;
    O5Color4f       HSV2RGB(const O5ColorHSV& Color) const;
    O5Color4f       HSV2RGB(float fH, float fS, float fV) const;
    
    float&          operator[](O5Byte bIndex) {return (&m_fH)[bIndex];}
    float           operator[](O5Byte bIndex) const {return (&m_fH)[bIndex];}

    float*          Pointer() {return &m_fH;}
    const float*    Pointer() const {return &m_fH;}
    
    float           m_fH;
    float           m_fS;
    float           m_fV;
};

inline O5ColorHSV O5ColorHSV::RGB2HSV(const O5Color4b& Color) const
{
    return RGB2HSV(O5Color4f(Color));
}

inline O5ColorHSV O5ColorHSV::RGB2HSV(float fR, float fG, float fB) const
{
    return RGB2HSV(O5Color4b(fR, fG, fB));
}

inline O5ColorHSV O5ColorHSV::RGB2HSV(O5Byte bR, O5Byte bG, O5Byte bB) const
{
    return RGB2HSV(O5Color4f(bR, bG, bB));
}

inline O5Color4f O5ColorHSV::HSV2RGB(float fH, float fS, float fV) const
{
    return HSV2RGB(O5ColorHSV(fH,fS,fV));
}

inline O5Color4f O5ColorHSV::HSV2RGB() const
{
    return HSV2RGB(*this);
}
