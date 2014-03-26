//
//  Vector.cpp
//  FactoryEngine
//
//  Created by Edvinas on 02/11/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#include <Geometry/Vector.h>

namespace ftr {
    
    
float Vector::CCWAngle(const glm::vec3& v1, const glm::vec3& v2)
{
    
    float angle = glm::angle(v1, v2);
    if (IsCWOrder(v1, v2)) {
        angle = 360 - angle;
    }
    return angle;
}
    
bool Vector::IsCWOrder(const glm::vec3& v1, const glm::vec3& v2)
{
    if (IsParallel(v1, v2)) {
        return false;
    }
    
    glm::vec3 cross = glm::cross(v1, v2);
    glm::vec3 xyzClosestAxis = XYZClosestAxis(cross);
    return glm::dot(cross, xyzClosestAxis) < 0;
}
    
bool Vector::IsParallel(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::isNull(glm::abs(v1) - glm::abs(v2), 0.0001f);
}
    
glm::vec3 Vector::XYZClosestAxis(glm::vec3 v)
{
    static const glm::vec3 axis[3] =
    {
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, -1.0f, 0.0f), //TODO: diferences in coordinates model. Not sure if this is right solution...
        glm::vec3(0.0f, 0.0f, 1.0f)
    };
    int maxIndex = 0;
    float max = 0;
    for (int i = 0; i < 3; i++) {
        float angle = glm::angle(glm::normalize(v), axis[i]);
        float diff = fabs(angle - 90);
        if (diff > max) {
            max = diff;
            maxIndex = i;
        }
    }
    return axis[maxIndex];
}
    
}

