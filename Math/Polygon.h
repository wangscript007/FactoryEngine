// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//
#pragma once

#include <Math/Geometry.h>

namespace Factory {

class Polygon
{
public:
    void Rotate(Vec3& vAngle);
    void Translate(Vec3& vOffset);
    void Scale(Vec3& vOffset);
    void Reset();
    
private:
    Mat4 m_mMatrix;
    Vec3 m_vLocal;
    Vec3 m_vWorld;
};

}