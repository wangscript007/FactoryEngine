
#pragma once

#include <Snapping/Snap.h>

namespace ftr {
    
class PointNode;
class Cylinder;
    
class PointSnap : public Snap
{
public:
    using Snap::Snap;
    virtual ~PointSnap() {}

    glm::vec3 Snapped() const;
    PointNode* SnappedPoint() const;
    
private:
    PointNode* NearestPointToCenterInSphere(const Sphere& sphere) const;
    PointNode* NearestPointToAxisInCylinder(const Cylinder& cylinder) const;
    
};
    
}

