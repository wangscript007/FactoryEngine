

#include <Scene/Camera.h>
#include <Main/Log.h>
#include <Math/Transformation.h>


namespace ftr {
    
const float Camera::kViewportScale = 0.3;

Camera::Camera(const Vec3& eyePosition)
    :mShadingInterface(NULL)
{
    mEyePosition = eyePosition;
    mTranslation = Vec3();
    mRotation = Vec3();
}
    
void Camera::Look()
{
    static const Vec3 target = Vec3();
    Vec3 forward = target + mEyePosition;
    forward.Normalize();
    Vec3 side = forward^Vec3::Y;
    side.Normalize();
    Mat4 rotation = Transformation::RotateAroundAxis(mRotation.mX, side);
    rotation *= Transformation::RotateAroundAxis(mRotation.mY, Vec3::Y);
    mTransform.view = Transformation::LookAt(mEyePosition, target, Vec3::Y);
    Mat4 tranbslation = Transformation::Translate(mTranslation);
    mParameters.modelviewMatrix = rotation * tranbslation * mTransform.view;
    mTransform.view = mParameters.modelviewMatrix;
    if (mShadingInterface) {
        mShadingInterface->InputTransform(mTransform);
    }
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    mTranslation.mX -= deltaMove.mX;
    mTranslation.mY += deltaMove.mY;
    
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    mRotation.mX += deltaRotation.mX;
    mRotation.mY += deltaRotation.mY;
    
    double ip;
    modf(mRotation.mX/360, &ip);
    mRotation.mX = mRotation.mX - ip*360;
    modf(mRotation.mY/360, &ip);
    mRotation.mY = mRotation.mY - ip*360;
    
}

void Camera::ZoomBy(const GLfloat times)
{
    mEyePosition.mX *= times;
    mEyePosition.mY *= times;
    mEyePosition.mZ *= times;
}

void Camera::setProjection(Projection projectionMode)
{
    mProjection = projectionMode;
    switch (projectionMode) {
        case kProjectionPerspective:
            mTransform.projection = Transformation::Frustum(-kViewportScale, kViewportScale,
                                                        -kViewportScale, kViewportScale,
                                                            2.0f, 200.0f);

            break;
        case kProjectionOrthographic:
            mTransform.projection = Transformation::Ortho(-kViewportScale, kViewportScale,
                                                      -kViewportScale, kViewportScale,
                                                      2.0f, 20.0);
            break;
    }
    mParameters.projectionMatrix = mTransform.projection;
}
    
void Camera::setViewport(const Frame& frame)
{
    float size = std::max(frame.GetWidth(), frame.GetHeight());
    glViewport(0.0f, 0.0f, size, size);
    mParameters.viewport = Frame(Vec2(), Vec2(size, size));
#ifndef GLES
    mShadingInterface->InputWindowSize(frame.GetExtent());
#endif
}
    
}


