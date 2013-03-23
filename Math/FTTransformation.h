
#pragma once

class FTTransformation
{
public:
    virtual ~FTTransformation() {}
    static O5Mat4 Move(const O5Vec3& vMotion);
};

O5Mat4 FTTransformation::Move(const O5Vec3& vMotion)
{
    O5Mat4 m = O5Mat4::Identity;
    m[3][0] = vMotion.m_fX;
    m[3][1] = vMotion.m_fY;
    m[3][2] = vMotion.m_fZ;
    return m;
}

