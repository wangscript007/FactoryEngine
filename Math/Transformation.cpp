
#include <Math/Transformation.h>

namespace Factory {

Mat4 Transformation::Move(const Vec3& vMotion)
{
    return Mat4(Vec4(1.0, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, 1.0, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, 1.0, 0.0f),
                  Vec4(vMotion.m_fX, vMotion.m_fY, vMotion.m_fZ, 1.0f)
                  );
}

Mat4 Transformation::Rotate(const Vec3& vRadians)
{
    Mat4 mx = Mat4::Identity;
    float cx = cosf(vRadians.m_fX);
    float sx = sinf(vRadians.m_fX);
    mx[1][1] = cx;
    mx[2][1] = sx;
    mx[1][2] = -sx;
    mx[2][2] = cx;
    
    Mat4 my = Mat4::Identity;
    float cy = cosf(vRadians.m_fY);
    float sy = sinf(vRadians.m_fY);
    my[0][0] = cy;
    my[2][0] = -sy;
    my[0][2] = sy;
    my[2][2] = cy;
    
    Mat4 mz = Mat4::Identity;
    float cz = cosf(vRadians.m_fZ);
    float sz = sinf(vRadians.m_fZ);
    mz[0][0] = cz;
    mz[1][0] = sz;
    mz[0][1] = -sz;
    mz[1][1] = cz;
    return mx*my*mz;
}

Mat4 Transformation::Scale(const Vec3& vScale)
{
    return Mat4(Vec4(vScale.m_fX, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, vScale.m_fY, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, vScale.m_fZ, 0.0f),
                  Vec4(0.0f, 0.0f, 0.0f, 1.0f)
                  );
}

}