#pragma once

#include <Model/Node.h>

namespace ftr {

class ModelManager;

class ScaleInteraction : public Node
{
public:
    ScaleInteraction(ModelManager& rModelManager);
    virtual ~ScaleInteraction() {}
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
