
#include <Interaction/CameraInteraction.h>
#include <Scene/Camera.h>

namespace ftr {
    
CameraInteraction::CameraInteraction(Camera& camera)
    :mCamera(camera)
{
    
}
    
#pragma mark Instance

void CameraInteraction::MoveBy(const Vec2 deltaMove)
{
    mCamera.MoveBy(deltaMove);
}

void CameraInteraction::Move(const Vec2 motion)
{
    
}
    
void CameraInteraction::RotateBy(const Vec2 deltaRotation)
{
    mCamera.RotateBy(deltaRotation);
}
    
void CameraInteraction::ZoomBy(const GLfloat times)
{
    mCamera.ZoomBy(times);
}
    
void CameraInteraction::Zoom(const GLfloat times)
{
    
}
    
void CameraInteraction::Look()
{
    mCamera.CreateTransformations();
}

   
    
    
}

