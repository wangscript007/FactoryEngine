#pragma once

#include <Model/FTNode.h>

class FTModelManager;

class FTRotationInteraction : public FTNode
{
public:
    FTRotationInteraction(FTModelManager& rModelManager);
    virtual ~FTRotationInteraction() {}
    void Render();
    
    void SetStart(O5Vec3 vStart);
    void SetEnd(O5Vec3 vEnd);
    
private:
    O5Vec3 m_vStart;
    O5Vec3 m_vEnd;
    FTNode* m_pNode;
    FTModelManager& m_rModelManager;
    bool m_bActive;
};

