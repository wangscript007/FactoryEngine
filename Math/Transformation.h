
#pragma once

namespace Factory {

class Transformation
{
public:
    virtual ~Transformation() {}
    static O5Mat4 Move(const O5Vec3& vMotion);
    static O5Mat4 Rotate(const O5Vec3& vMotion);
    static O5Mat4 Scale(const O5Vec3& vScale);
};

}

