
#pragma once

#include <Graph/Node.h>

namespace ftr {
    
class Camera;

class CameraInteraction
{
public:
    CameraInteraction(Camera& camera);
    virtual ~CameraInteraction() {}
    
    void MoveBy(const glm::vec2 deltaMove);
    void Move(const glm::vec2 motion);
    void RotateBy(const glm::vec2 deltaRotation);
    void ZoomBy(const GLfloat times, const glm::vec2& toViewportPoint);
    void Zoom(const GLfloat times);
    void Look();
    
private:
    Camera& mCamera;
};
    
}

