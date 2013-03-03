

#pragma once

#include <Model/FTNode.h>
#include <Math/FTGeometry.h>
#include <Math/FTPolygon.h>

class  FTModelManager;

class FTRectangleInteraction : public FTNode
{
public:
    
    
    FTRectangleInteraction(FTModelManager& rModelManager);
    virtual ~FTRectangleInteraction() {}
    
    void Render();
    void Begin();
    void End();
    void SetOrigin(const O5Vec3& vOrigin);
    void SetCurrent(const O5Vec3& vCurrent);
    
    
private:
    FTPolygon m_cPolygon;
    FTRectangle3 m_sRect3;
    FTModelManager& m_rModelManager;
    bool m_bActive;
};

