
#pragma once
    
#include <Math/GeometryPrimitives.h>
#include <Math/Segment.h>

namespace ftr {

class Cylinder
{
public:
    Cylinder(const Segment& axis, float radius)
    : mAxis(axis), mRadius(radius) {};
    virtual ~Cylinder() {};
    
    Segment mAxis;
    float mRadius;
    
    bool Intersects(const Box& box) const;
};
    
}

