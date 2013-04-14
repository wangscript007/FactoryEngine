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
