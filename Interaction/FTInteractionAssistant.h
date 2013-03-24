
#pragma once

class FTInteractionAssistant
{
public:
    static const float c_fSensitivity;
    
    virtual ~FTInteractionAssistant() {}
    O5Vec3 AxisAlignedViewport(const O5Vec3& vStartScene, const O5Vec3& vEndViewport) const;
    
private:
};

