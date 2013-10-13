
#pragma once

#include <Snapping/Snap.h>

namespace ftr {

class AxisSnap : public Snap
{
public:
    using Snap::Snap;
    virtual ~AxisSnap() {}
    
    glm::vec3 Snapped() const;
};
    
}

