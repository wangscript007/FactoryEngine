
#pragma once

#include "FTModel.h"

class FTPoint : public FTModel
{
public:
    static const float c_fR;
    
    FTPoint();
    virtual ~FTPoint() {}
    
    void SetOrigin(O5Vec3 vOrigin) { m_vOrigin = vOrigin; }
    O5Vec3& GetOrigin() { return m_vOrigin; }
    virtual void Render();
    
private:
    
    O5Vec3 m_vOrigin;
};

