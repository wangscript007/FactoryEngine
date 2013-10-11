
#pragma once

#include <Math/Segment.h>

namespace ftr {

class Viewport
{
public:
    virtual ~Viewport() {}
    
    static float DepthAtPoint(const glm::vec2& point);
    
    glm::mat4 projectionMatrix;
    glm::mat4 modelviewMatrix;
    glm::vec4 frame;
    
    glm::vec2 CoordsAt(const glm::vec3& sceneCoords) const;
    glm::vec3 SceneCoordsAt(const glm::vec2& viewportCoords) const;
    Segment RayAtPoint(const glm::vec2& point) const;
    
private:
    glm::vec3 Project(const glm::vec3& sceneVec) const;
    glm::vec3 UnProject(const glm::vec3& windowVec) const;
    
    
};
    
}

