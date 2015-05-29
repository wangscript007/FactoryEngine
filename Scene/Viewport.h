
#pragma once

#include <Geometry/Segment.h>
#include <Geometry/Triangle.h>

namespace ftr {

class Viewport
{
public:
    virtual ~Viewport() {}
    
    static std::vector<glm::vec3> mDebugPoints;
    static void AddDebugPoint(const glm::vec2& point);
    
    static float DepthAtPoint(const glm::vec2& point);
    
    glm::mat4 projectionMatrix;
    glm::mat4 modelviewMatrix;
    glm::vec4 frame;
    
    glm::vec2 CoordsAt(const glm::vec3& sceneCoords) const;
    glm::vec3 SceneCoordsAt(const glm::vec2& viewportCoords) const;
    glm::vec3 SceneCoordsAtCenter() const;
    Segment RayAtPoint(const glm::vec2& point) const;
    Triangle Plane() const;
    bool InFront(const glm::vec3& coords) const;
    bool IsVisible(const glm::vec3& coords) const;
    
private:
    glm::vec3 Project(const glm::vec3& sceneVec) const;
    glm::vec3 UnProject(const glm::vec3& windowVec) const;
    glm::vec2 Center() const;
    
    
};
    
}

