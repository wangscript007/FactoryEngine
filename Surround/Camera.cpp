

#include <Surround/Camera.h>
#include <Main/Log.h>
#include <Math/Transformation.h>


namespace ftr {

Camera::Camera(const Vec3& eyePosition)
    :mShadersInput(NULL)
{
    mEyePosition = eyePosition;
}
    
void Camera::Look()
{
    static const Vec3 zero = Vec3();
    mModelMatrix = Transformation::LookAt(mEyePosition, zero, Vec3::Y);
    mModelMatrix *= Transformation::Translate(mTranslation);
    mModelMatrix *= Transformation::Rotate(mRotation);
    
    if (mShadersInput) {
        mShadersInput->InputProjectionMatrix(&mProjectionMatrix);
        mShadersInput->InputViewMatrix(&mModelMatrix);
    }
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    mTranslation.mX += deltaMove.mX/10.0f;
    mTranslation.mY += deltaMove.mY/10.0f;
    
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    mRotation.mX += deltaRotation.mX/10.0f;
    mRotation.mY += deltaRotation.mY/10.0f;
    
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
        case kProjectionProjection:
            mProjectionMatrix = Transformation::Frustum(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, 2000.0);
            break;
        case kProjectionOrthographic:
            mProjectionMatrix = Transformation::Ortho(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, 2000.0);
            break;
    }
}
    

}


