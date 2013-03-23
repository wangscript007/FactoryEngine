
#pragma once

class FTTransformation
{
public:
    virtual ~FTTransformation() {}
    static O5Mat4 Move(const O5Vec3& vMotion);
    static O5Mat4 Rotate(const O5Vec3& vMotion);
};



