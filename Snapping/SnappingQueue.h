
#pragma once

#include <Snapping/Snap.h>
#include <Scene/Viewport.h>
#include <Processing/ModelTree.h>

namespace ftr {

class SnappingQueue : public Snap
{
public:
    typedef std::vector <Snap*> SnapsVector;
    
    SnappingQueue(const Viewport& viewport, const Picker& picker, const ModelTree& modelTree);
    virtual ~SnappingQueue() {};
    
    glm::vec3 Snapped() const;
    
private:
    SnapsVector mSnapsVector;
};
    
}

