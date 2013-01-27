
#pragma once

#include <Model/FTNode.h>

class FTModelManager;
class FTPoint;

class FTLineInteraction : public FTNode
{
public:
    FTLineInteraction(FTModelManager& rModelManager);
    virtual ~FTLineInteraction() {}
    void Render();
    void Begin();
    void Step();
    void End();
    void SetStart(O5Vec3 vStart);
    void SetEnd(O5Vec3 vEnd);
    
    
private:
    FTModelManager& m_rModelManager;
    O5Vec3 m_vStart;
    O5Vec3 m_vEnd;
    bool m_bActive;
    FTPoint* m_pStartPoint;
    FTPoint* m_pEndPoint;

};

