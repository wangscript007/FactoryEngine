

#include <Scene/Camera.h>
#include <Main/Log.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>


namespace ftr {
    
const float Camera::kViewportScale = 0.3;

Camera::Camera(const glm::vec3& eyePosition)
    :mShadingInterface(NULL)
{
    mEyePosition = eyePosition;
    mTranslation = glm::vec3();
    mRotation = glm::vec3();
}
    
void Camera::CreateTransformations()
{
    static const glm::vec3 target = glm::vec3(0.0f);
    glm::vec3 forward = target + mEyePosition;
    forward = glm::normalize(forward);
    glm::vec3 axisY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 side = glm::normalize(glm::cross(forward, axisY));
    glm::mat4 rotation = glm::rotate(mRotation.x, side);
    rotation *= glm::rotate(mRotation.y, axisY);
    mTransform.view = glm::lookAt(mEyePosition, target, axisY);
    glm::mat4 translation = glm::translate(mTranslation);
    mParameters.modelviewMatrix = rotation * translation * mTransform.view;
    mTransform.view = mParameters.modelviewMatrix;
}
    
void Camera::CommitTransformations()
{
    if (mShadingInterface) {
        mShadingInterface->InputTransform(mTransform);
    }
}

void Camera::MoveBy(const glm::vec2 deltaMove)
{
    mTranslation.x += deltaMove.x;
    mTranslation.y += deltaMove.y;
    
}

void Camera::RotateBy(const glm::vec2 deltaRotation)
{
    mRotation.x -= deltaRotation.x;
    mRotation.y += deltaRotation.y;
    
    double ip;
    modf(mRotation.x/360, &ip);
    mRotation.x = mRotation.x - ip*360;
    modf(mRotation.y/360, &ip);
    mRotation.y = mRotation.y - ip*360;
    
}

void Camera::ZoomBy(const GLfloat times)
{
    mEyePosition.x *= times;
    mEyePosition.y *= times;
    mEyePosition.z *= times;
}

void Camera::setProjection(Projection projectionMode)
{
    mProjection = projectionMode;
    switch (projectionMode) {
        case kProjectionPerspective: {
            glm::mat4 mat = glm::perspective(60.0f, 1.0f, 0.1f, 10000.f);
            mTransform.projection = *((glm::mat4*)glm::value_ptr(mat));
            break;
        }
        case kProjectionOrthographic: {
            glm::mat4 mat = glm::perspective(60.0f, 1.0f, 0.1f, 10000.f);
            mTransform.projection = *((glm::mat4*)glm::value_ptr(mat));
        } break;
    }
    mParameters.projectionMatrix = mTransform.projection;
}
    
void Camera::setViewport(const  glm::vec4& frame)
{
    float width = fabsf(frame[0] - frame[2]);
    float height = fabsf(frame[1] - frame[3]);
    float size = std::max(width, height);
    glViewport(0.0f, 0.0f, size, size);
    mParameters.viewport =  glm::vec4(glm::vec2(), glm::vec2(size, size));
#ifndef GLES
    mShadingInterface->InputWindowSize(glm::vec2(size, size));
#endif
}
    
}


