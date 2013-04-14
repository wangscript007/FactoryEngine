#pragma once

#include <Model/Node.h>

namespace ftr {

class ModelManager;

class MoveInteraction : public Node
{
public:
    MoveInteraction(ModelManager& rModelManager);
    virtual ~MoveInteraction() {}
    void Render();
    
    void SetStart(Vec3 vStart);
    void SetEnd(Vec3 vEnd);
    
private:
    Vec3 m_vStart;
    Vec3 m_vEnd;
    Node* m_pNode;
    ModelManager& m_rModelManager;
    bool m_bActive;
};
    
}

