
#include <Math/Transformation.h>

namespace ftr {

Mat4 Transformation::Translate(const Vec3& motion)
{
    return Mat4(Vec4(1.0, 0.0f, 0.0f, 0.0f),
                  Vec4(0.0f, 1.0, 0.0f, 0.0f),
                  Vec4(0.0f, 0.0f, 1.0, 0.0f),
                  Vec4(motion.mX, motion.mY, motion.mZ, 1.0f)
                  );
}

Mat4 Transformation::Rotate(const Vec3& radians)
{
    Mat4 mx, my, mz;
    float cx = cosf(radians.mX);
    float sx = sinf(radians.mX);
    mx[1][1] = cx;
    mx[2][1] = sx;
    mx[1][2] = -sx;
    mx[2][2] = cx;
    
    float cy = cosf(radians.mY);
    float sy = sinf(radians.mY);
    my[0][0] = cy;
    my[2][0] = -sy;
    my[0][2] = sy;
    my[2][2] = cy;
    
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
                Vec4(0.0f, 0.0f, 0.0f, 1.0f));
}
    
    
Mat4 Transformation::Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                             GLdouble near, GLdouble far)
{
    Mat4 m;
    m.mX[0] = 2.0f*near/(right - left);
    m.mY[1] = 2.0f*near/(top - bottom);
    m.mX[2] = (right + left)/(right - left);
    m.mY[2] = (top + bottom)/(top - bottom);
    m.mZ[2] = -(far + near)/(far - near);
    m.mZ[3] = -(2.0f*far*near)/(far - near);
    m.mW[2] = -1.0f;
    m.mW[3] = 0.0f;
    return m;
}
    
Mat4 Transformation::Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                                  GLdouble near, GLdouble far)
{
    Mat4 m;
    m.mX[0] = 2.0f/(right - left);
    m.mY[1] = 2.0f/(top - bottom);
    m.mZ[2] = -2.0/(far-near);
    
    m.mX[3] = -(right + left)/(right - left);
    m.mY[3] = -(top + bottom)/(top - bottom);
    m.mZ[3] = -(far + near)/(far - near);
    m.mW[3] = 1.0f;
    return m;
}
    
 Mat4 Transformation::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
    Mat4 m;
    Vec3 side, up2;
    Vec3 forward = center - eye;
    forward.Normalize();
    side = forward^up;
    side.Normalize();
    up2 = side^forward;
    
    m.mX[0] = side[0];
    m.mY[0] = side[1];
    m.mZ[0] = side[2];
    m.mW[0] = 0.0f;
    
    m.mX[1] = up2[0];
    m.mY[1] = up2[1];
    m.mZ[1] = up2[2];
    m.mW[1] = 0.0f;
    
    m.mX[2] = -forward[0];
    m.mY[2] = -forward[1];
    m.mZ[2] = -forward[2];
    m.mW[2] = 0.0f;
    
    m.mX[3] = 0;
    m.mY[3] = 0;
    m.mZ[3] = 0;
    m.mZ[3] = 1.0f;
    
    m *= Translate(eye);
    return m;
}

}
