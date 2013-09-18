
#pragma once

namespace ftr {

class Transformation
{
public:
    virtual ~Transformation() {}
    static Mat4 Translate(const Vec3& motion);
    static Mat4 Rotate(const Vec3& angle);
    static Mat4 RotateAroundAxis(float angle, const Vec3& axis);
    static Mat4 Scale(const Vec3& scale);
    
    static Mat4 Frustum(FTDouble left, FTDouble right, FTDouble bottom, FTDouble top,
                        FTDouble near, FTDouble far);
    static Mat4 Perspective(float fov, float ratio, float nearP, float farP);
    static Mat4 Ortho(FTDouble left, FTDouble right, FTDouble bottom, FTDouble top,
                      FTDouble near, FTDouble far);
    
    static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
};

}

