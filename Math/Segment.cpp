//
//  Segment.cpp
//  FactoryEngine
//
//  Created by Edvinas on 10/9/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#include <Math/Segment.h>

namespace ftr {

float Segment::DistanceFromPoint(const glm::vec3& point)
{
    return glm::length(NearestPoint(point) - point);
}
    
glm::vec3 Segment::NearestPoint(const glm::vec3 &testPoint)
{
    const glm::vec3 A = testPoint - mStart;
    const glm::vec3 u = glm::normalize((mStart-mEnd));
    return mStart + glm::dot(A, u) * u;
};

}