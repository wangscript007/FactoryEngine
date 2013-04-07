
#include <Math/Transformation.h>

namespace Factory {

O5Mat4 Transformation::Move(const O5Vec3& vMotion)
{
    return O5Mat4(O5Vec4(1.0, 0.0f, 0.0f, 0.0f),
                  O5Vec4(0.0f, 1.0, 0.0f, 0.0f),
                  O5Vec4(0.0f, 0.0f, 1.0, 0.0f),
                  O5Vec4(vMotion.m_fX, vMotion.m_fY, vMotion.m_fZ, 1.0f)
                  );
}

O5Mat4 Transformation::Rotate(const O5Vec3& vRadians)
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
    return mx*my*mz;
}

O5Mat4 Transformation::Scale(const O5Vec3& vScale)
{
    return O5Mat4(O5Vec4(vScale.m_fX, 0.0f, 0.0f, 0.0f),
                  O5Vec4(0.0f, vScale.m_fY, 0.0f, 0.0f),
                  O5Vec4(0.0f, 0.0f, vScale.m_fZ, 0.0f),
                  O5Vec4(0.0f, 0.0f, 0.0f, 1.0f)
                  );
}

}