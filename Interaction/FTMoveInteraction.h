#pragma once

#include <Model/FTNode.h>

class FTModelManager;

class FTMoveInteraction : public FTNode
{
public:
    FTMoveInteraction(FTModelManager& rModelManager);
    virtual ~FTMoveInteraction() {}
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

