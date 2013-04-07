
#pragma once

namespace Factory {

class InteractionAssistant
{
public:
    static const float c_fSensitivity;
    
    virtual ~InteractionAssistant() {}
    O5Vec3 AxisAlignedViewport(const O5Vec3& vStartScene, const O5Vec3& vEndViewport) const;
    
private:
};
    
}

