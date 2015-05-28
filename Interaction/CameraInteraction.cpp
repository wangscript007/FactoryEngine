
#include <Interaction/CameraInteraction.h>
#include <Scene/Camera.h>

namespace ftr {
    
CameraInteraction::CameraInteraction(Camera& camera)
    :mCamera(camera)
{
    
}
    
#pragma mark Instance

void CameraInteraction::MoveBy(const glm::vec2 deltaMove)
{
    mCamera.MoveBy(deltaMove);
    mCamera.CreateTransformations();
}

void CameraInteraction::Move(const glm::vec2 motion)
{
    
}
    
void CameraInteraction::RotateBy(const glm::vec2 deltaRotation)
{
    mCamera.RotateBy(deltaRotation);
    mCamera.CreateTransformations();
}
    
void CameraInteraction::ZoomBy(const GLfloat times, const glm::vec2& toViewportPoint)
{
    mCamera.ZoomBy(times, toViewportPoint);
    mCamera.CreateTransformations();
}
    
void CameraInteraction::Zoom(const GLfloat times)
{
    
}
    
   
    
    
}

