
#pragma once

class FTPoint : public FTModel
{
public:
    FTPoint();
    virtual ~FTPoint() {}
    
    void SetOrigin(O5Vec3 vOrigin) { m_vOrigin = vOrigin; }
    virtual void Render();
    
private:
    O5Vec3 m_vOrigin;
};

