//
//  Vector.h
//  FactoryEngine
//
//  Created by Edvinas on 02/11/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#pragma once

namespace ftr {

class Vector
{
public:
    virtual ~Vector() {}
    static bool IsCWOrder(const glm::vec3& v1, const glm::vec3& v2);
    static float CCWAngle(const glm::vec3& v1, const glm::vec3& v2);
    static glm::vec3 XYZClosestAxis(glm::vec3 v);
private:
    
    
};
    
}

