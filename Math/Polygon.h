// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//
#pragma once

#include <Math/Geometry.h>

namespace ftr {

class Polygon
{
public:
    void Rotate(Vec3& angle);
    void Translate(Vec3& offset);
    void Scale(Vec3& offset);
    void Reset();
    
private:
    Mat4 m_mMatrix;
    Vec3 mLocal;
    Vec3 mWorld;
};

}