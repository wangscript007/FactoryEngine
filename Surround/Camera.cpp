

#include <Surround/Camera.h>
#include <Main/Log.h>
#include <Math/Transformation.h>


namespace ftr {

Camera::Camera(const Vec3& eyePosition)
    :mShadersInput(NULL)
{
    mEyePosition = eyePosition;
    mTranslation = Vec3();
    mRotation = Vec3();
}
    
void Camera::Look()
{
    static const Vec3 zero = Vec3(0.0f, 0.0f, 0.0f);
    //mModelMatrix = ;
    mModelMatrix = Transformation::Rotate(mRotation);
    mModelMatrix *= Transformation::Translate(mTranslation);
    mModelMatrix *= Transformation::Translate(-mEyePosition);
    mModelMatrix *= Transformation::Translate(-Vec3(5.0f, 5.0f, 20.0));
    if (mShadersInput) {
        mShadersInput->InputProjectionMatrix(&mProjectionMatrix);
        mShadersInput->InputViewMatrix(&mModelMatrix);
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
    mRotation.mX -= deltaRotation.mX/10;
    mRotation.mY -= deltaRotation.mY/10;
    
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
            mProjectionMatrix = Transformation::Frustum(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, 100.0);
            break;
        case kProjectionOrthographic:
            mProjectionMatrix = Transformation::Ortho(-1.0f, 1.0f, -1.0f, 1.0f, 2.0f, 100.0);
            break;
    }
}
    
void Camera::setViewport(const Frame& frame)
{
    float size = std::max(frame.GetWidth(), frame.GetHeight());
    glViewport(0.0f, 0.0f, size, size);
    //mProjectionMatrix = Transformation::Frustum(-0.1f, 0.1f, -0.1f, 0.1f, 2.0f, 2000.0);
}
    

}


