
#include <Math/Transformation.h>

namespace ftr {

Mat4 Transformation::Move(const Vec3& motion)
{
    return Mat4(Vec4(1.0, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, 1.0, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, 1.0, 0.0f),
                  Vec4(motion.mX, motion.mY, motion.mZ, 1.0f)
                  );
}

Mat4 Transformation::Rotate(const Vec3& radians)
{
    Mat4 mx = Mat4::Identity;
    float cx = cosf(radians.mX);
    float sx = sinf(radians.mX);
    mx[1][1] = cx;
    mx[2][1] = sx;
    mx[1][2] = -sx;
    mx[2][2] = cx;
    
    Mat4 my = Mat4::Identity;
    float cy = cosf(radians.mY);
    float sy = sinf(radians.mY);
    my[0][0] = cy;
    my[2][0] = -sy;
    my[0][2] = sy;
    my[2][2] = cy;
    
    Mat4 mz = Mat4::Identity;
    float cz = cosf(radians.mZ);
    float sz = sinf(radians.mZ);
    mz[0][0] = cz;
    mz[1][0] = sz;
    mz[0][1] = -sz;
    mz[1][1] = cz;
    return mx*my*mz;
}

Mat4 Transformation::Scale(const Vec3& scale)
{
    return Mat4(Vec4(scale.mX, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, scale.mY, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, scale.mZ, 0.0f),
                  Vec4(0.0f, 0.0f, 0.0f, 1.0f)
                  );
}

}