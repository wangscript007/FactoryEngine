

#include <Scene/Camera.h>
#include <Main/Log.h>
#include <Math/Transformation.h>


namespace ftr {
    
const float Camera::kViewportScale = 0.3f;

Camera::Camera(const Vec3& eyePosition)
    :mShadersInput(NULL)
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
    mTransform.rotation = Transformation::RotateAroundAxis(mRotation.mX, side);
    mTransform.rotation *= Transformation::RotateAroundAxis(mRotation.mY, Vec3::Y);
    mTransform.view = Transformation::LookAt(mEyePosition, target, Vec3::Y);
    mTransform.translation = Transformation::Translate(mTranslation);
    if (mShadersInput) {
        mShadersInput->InputTransform(mTransform);
    }
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    mTranslation.mX += deltaMove.mX;
    mTranslation.mY += deltaMove.mY;
    //mTranslation.mZ -= deltaMove.mX;
    
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    mRotation.mX -= deltaRotation.mX;
    mRotation.mY -= deltaRotation.mY;
    
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
                                                        2.0f, 2000.0);
            break;
        case kProjectionOrthographic:
            mTransform.projection = Transformation::Ortho(-kViewportScale, kViewportScale,
                                                      -kViewportScale, kViewportScale,
                                                      2.0f, 2000.0);
            break;
    }
}
    
void Camera::setViewport(const Frame& frame)
{
    float size = std::max(frame.GetWidth(), frame.GetHeight());
    glViewport(0.0f, 0.0f, size, size);
    mShadersInput->InputWindowSize(frame.GetExtent());
}
    

}


