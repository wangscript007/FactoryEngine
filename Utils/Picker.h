#pragma once

#include <Scene/Camera.h>
#include <Math/Segment.h>

namespace ftr {

class Picker
{
public:
    static glm::vec3 Viewport(const glm::vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static glm::vec2 Viewport2(const glm::vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static glm::vec3 Scene(const glm::vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static GLfloat DepthAtPoint(const glm::vec2& point);
    static glm::vec3 GluProject(const glm::vec3& sceneVec, const Camera::Parameters& cameraParameters);
    static glm::vec3 GluUnProject(const glm::vec3& windowVec, const Camera::Parameters& cameraParameters);
    static Segment RayAtPoint(const glm::vec2& point, const Camera::Parameters& cameraParameters);
};
    
}

