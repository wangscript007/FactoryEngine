
#pragma once

namespace Factory {

class InteractionAssistant
{
public:
    static const float c_fSensitivity;
    
    virtual ~InteractionAssistant() {}
    Vec3 AxisAlignedViewport(const Vec3& vStartScene, const Vec3& vEndViewport) const;
    
private:
};
    
}

