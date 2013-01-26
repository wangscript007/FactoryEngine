#include <Model/FTNode.h>

#pragma once

class FTRectangleInteraction : public FTNode
{
public:
    virtual ~FTRectangleInteraction() {}
    
    void Render();
    void Begin();
    void End();
    void SetSize(const O5Vec3 vSize);
    const O5Vec3& Size() const { return m_vSize; }
    void SetOrigin(const O5Vec3 vOrigin);
    const O5Vec3& Origin() const { return m_vOrigin; }
    
private:
    O5Vec3 m_vOrigin;
    O5Vec3 m_vSize;
};

