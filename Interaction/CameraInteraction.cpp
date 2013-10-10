
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
}

void CameraInteraction::Move(const glm::vec2 motion)
{
    
}
    
void CameraInteraction::RotateBy(const glm::vec2 deltaRotation)
{
    mCamera.RotateBy(deltaRotation);
}
    
void CameraInteraction::ZoomBy(const GLfloat times, const glm::vec2& toViewportPoint)
{
    mCamera.ZoomBy(times, toViewportPoint);
}
    
void CameraInteraction::Zoom(const GLfloat times)
{
    
}
    
void CameraInteraction::Look()
{
    mCamera.CreateTransformations();
}

   
    
    
}

