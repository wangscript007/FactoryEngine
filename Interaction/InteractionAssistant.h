
#pragma once

namespace ftr {

class InteractionAssistant
{
public:
    static const float kSensitivity;
    
    virtual ~InteractionAssistant() {}
    Vec3 AxisAlignedViewport(const Vec3& startScene, const Vec3& endViewport) const;
    
private:
};
    
}

