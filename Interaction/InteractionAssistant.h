
#pragma once

#include <Scene/Camera.h>

namespace ftr {

class InteractionAssistant
{
public:
    static const float kSensitivity;
    
    virtual ~InteractionAssistant() {}
    Vec3 AxisAlignedViewport(const Vec3& startScene,
                             const Vec2& endViewport,
                             const Camera::Parameters& cameraParameters) const;
    
private:
};
    
}

