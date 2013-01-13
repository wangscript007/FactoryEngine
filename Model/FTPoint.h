
#pragma once

#include <Model/FTModel.h>

class FTPoint : public FTModel
{
public:
    static const float c_fR;
    
    FTPoint();
    virtual ~FTPoint() {}
    
    O5Vec3 m_vOrigin;
    
    virtual void Render();
    
private:
    
    
};

