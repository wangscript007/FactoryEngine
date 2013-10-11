
#pragma once

#include <Scene/Camera.h>

namespace ftr {

class InteractionAssistant
{
public:
    static const float kSensitivity;
    
    virtual ~InteractionAssistant() {}
    glm::vec3 AxisAlignedViewport(const glm::vec3& startScene,
                                  const glm::vec2& endViewport) const;
    
private:
};
    
}

