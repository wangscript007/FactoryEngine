
#pragma once

namespace ftr {

class Transformation
{
public:
    virtual ~Transformation() {}
    static Mat4 Move(const Vec3& motion);
    static Mat4 Rotate(const Vec3& motion);
    static Mat4 Scale(const Vec3& scale);
};

}

