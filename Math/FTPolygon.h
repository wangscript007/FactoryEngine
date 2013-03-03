// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//
#pragma once

#include <Math/FTGeometry.h>

class FTPolygon
{
public:
    void Rotate(O5Vec3& vAngle);
    void Translate(O5Vec3& vOffset);
    void Scale(O5Vec3& vOffset);
    void Reset();
    
private:
    O5Mat4 m_mMatrix;
    O5Vec3 m_vLocal;
    O5Vec3 m_vWorld;
};

