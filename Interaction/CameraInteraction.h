
#pragma once

#include <Model/Node.h>

namespace ftr {
    
class Camera;

class CameraInteraction
{
public:
    CameraInteraction(Camera& camera);
    virtual ~CameraInteraction() {}
    
    void MoveBy(const Vec2 deltaMove);
    void Move(const Vec2 motion);
    void RotateBy(const Vec2 deltaRotation);
    void ZoomBy(const GLfloat times);
    void Zoom(const GLfloat times);
    void Look();
    
private:
    Camera& mCamera;
};
    
}

