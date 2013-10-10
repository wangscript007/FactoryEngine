// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//
#pragma once

#include <Math/Geometry.h>

namespace ftr {

class Polygon
{
public:
    void Rotate(glm::vec3& angle);
    void Translate(glm::vec3& offset);
    void Scale(glm::vec3& offset);
    void Reset();
    
private:
    glm::mat4 m_mMatrix;
    glm::vec3 mLocal;
    glm::vec3 mWorld;
};

}