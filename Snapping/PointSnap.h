
#pragma once

#include <Snapping/Snap.h>

namespace ftr {
    
class PointSnap : public Snap
{
public:
    using Snap::Snap;
    virtual ~PointSnap() {}

    glm::vec3 Snapped() const;
private:
    PointNode* NearestPointToCenterInSphere(const Sphere& sphere) const;
    
};
    
}

