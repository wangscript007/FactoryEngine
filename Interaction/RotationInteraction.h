#pragma once

#include <Model/Node.h>

namespace Factory {

class ModelManager;

class RotationInteraction : public Node
{
public:
    RotationInteraction(ModelManager& rModelManager);
    virtual ~RotationInteraction() {}
    void Render();
    
    void SetStart(O5Vec3 vStart);
    void SetEnd(O5Vec3 vEnd);
    
private:
    O5Vec3 m_vStart;
    O5Vec3 m_vEnd;
    Node* m_pNode;
    ModelManager& m_rModelManager;
    bool m_bActive;
};

}
