#pragma once

#include <Model/FTNode.h>

class FTModelManager;

class FTMoveInteraction : public FTNode
{
public:
    FTMoveInteraction(FTModelManager& rModelManager);
    virtual ~FTMoveInteraction() {}
    void Render();
    
    void SetMotion(O5Vec3 vMotion);
    
private:
    O5Vec3 m_vMotion;
    FTNode* m_pNode;
    FTModelManager& m_rModelManager;
    bool m_bActive;
};

