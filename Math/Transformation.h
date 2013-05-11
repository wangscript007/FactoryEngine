
#pragma once

namespace ftr {

class Transformation
{
public:
    virtual ~Transformation() {}
    static Mat4 Translate(const Vec3& motion);
    static Mat4 Rotate(const Vec3& motion);
    static Mat4 Scale(const Vec3& scale);
    
    static Mat4 Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                        GLdouble near, GLdouble far);
    static Mat4 Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
                      GLdouble near, GLdouble far);
    
    static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
};

}

