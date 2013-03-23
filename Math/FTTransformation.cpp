
#include <Math/FTTransformation.h>


O5Mat4 FTTransformation::Move(const O5Vec3& vMotion)
{
    O5Mat4 m = O5Mat4::Identity;
    m[3][0] = vMotion.m_fX;
    m[3][1] = vMotion.m_fY;
    m[3][2] = vMotion.m_fZ;
    return m;
}

O5Mat4 FTTransformation::Rotate(const O5Vec3& vRadians)
{
    O5Mat4 mx = O5Mat4::Identity;
    float cx = cosf(vRadians.m_fX);
    float sx = sinf(vRadians.m_fX);
    mx[1][1] = cx;
    mx[2][1] = sx;
    mx[1][2] = -sx;
    mx[2][2] = cx;
    
    O5Mat4 my = O5Mat4::Identity;
    float cy = cosf(vRadians.m_fY);
    float sy = sinf(vRadians.m_fY);
    my[0][0] = cy;
    my[2][0] = -sy;
    my[0][2] = sy;
    my[2][2] = cy;
    
    O5Mat4 mz = O5Mat4::Identity;
    float cz = cosf(vRadians.m_fZ);
    float sz = sinf(vRadians.m_fZ);
    mz[0][0] = cz;
    mz[1][0] = sz;
    mz[0][1] = -sz;
    mz[1][1] = cz;
    return my;
}

