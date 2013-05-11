

#include <Surround/Camera.h>
#include <Main/Log.h>
#include <Math/Transformation.h>


namespace ftr {

Camera::Camera()
    :mShadersInput(NULL),
    mMatrix(Mat4::Identity),
    mProjectionMatrix(Mat4::Identity)
    
{
    Reset();
    
}

Camera::Camera(const Vec3 coords)
{
    Camera();
}

void Camera::Reset()
{
    Frustum(-1, 1, -1, 1, 2.0f, 2000.0);
    LookAt(Vec3(-10.0f, -2.0f, -10.0f), Vec3(0.0f, 2.0f, -5.0f), Vec3(0.0f, 1.0f, 0.0f));
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    if (mShadersInput) {
        mShadersInput->InputViewMatrix(&mMatrix);
    } 
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    return;
    mMatrix *= Transformation::Rotate(Vec3(deltaRotation.mX, deltaRotation.mY, 0.0));
    if (mShadersInput) {
        mShadersInput->InputProjectionMatrix(&mMatrix);
    }
}

void Camera::ZoomBy(const GLfloat times)
{
    //mMatrix *= Mat4::Identity*times;
}

void Camera::setProjectionMode(ProjectionMode projectionMode)
{
    return;
    mProjectionMode = projectionMode;
    switch (projectionMode) {
        case kProjectionModeProjection:
            Frustum(-1, 1, -1, 1, 2.0f, 2000.0);
            break;
        case kProjectionModeOrthographic:
            Ortho(-5, 1, -1, 1, 2.0f, 2000.0);
            break;
    }
}
 
    /*
void Camera::Projection(float fov, float ratio, float nearP, float farP)
{
    mProjectionMatrix.Identity;
    float f = 1.0f / tan (fov * (M_PI / 360.0));
    setIdentityMatrix(mat,4);
    
    mat[0] = f / ratio;
    mat[1 * 4 + 1] = f;
    mat[2 * 4 + 2] = (farP + nearP) / (nearP - farP);
    mat[3 * 4 + 2] = (2.0f * farP * nearP) / (nearP - farP);
    mat[2 * 4 + 3] = -1.0f;
    mat[3 * 4 + 3] = 0.0f;
}
     */
    
void Camera::Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
{
    mProjectionMatrix = Mat4::Identity;
    mProjectionMatrix.mX[0] = 2*near/(right - left);
    mProjectionMatrix.mY[1] = 2*near/(top - bottom);
    mProjectionMatrix.mX[2] = (right + left)/(right - left); // A
    mProjectionMatrix.mY[2] = (top + bottom)/(top - bottom); // B
    mProjectionMatrix.mZ[2] = (far + near)/(far - near); // C
    mProjectionMatrix.mZ[3] = (2*far*near)/(far - near); // D
    mProjectionMatrix.mW[2] = -1;
    mProjectionMatrix.mW[3] = 0;
    if (mShadersInput) {
        mShadersInput->InputProjectionMatrix(&mProjectionMatrix);
    }
}
    
void Camera::Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
{
    
}
    
void Camera::LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
    Vec3 side, up2;
    Vec3 forward = center - eye;
    forward.Normalize();
    side = forward^up;
    side.Normalize();
    up2 = side^forward;
    
    mMatrix.mX[0] = side[0];
    mMatrix.mY[0] = side[1];
    mMatrix.mZ[0] = side[2];
    mMatrix.mW[0] = 0.0f;
    
    mMatrix.mX[1] = up2[0];
    mMatrix.mY[1] = up2[1];
    mMatrix.mZ[1] = up2[2];
    mMatrix.mW[1] = 0.0f;
    
    mMatrix.mX[2] = -forward[0];
    mMatrix.mY[2] = -forward[1];
    mMatrix.mZ[2] = -forward[2];
    mMatrix.mW[2] = 0.0f;
    
    mMatrix.mX[3] = 0;
    mMatrix.mY[3] = 0;
    mMatrix.mZ[3] = 0;
    mMatrix.mZ[3] = 1.0f;
    
    mMatrix *= Transformation::Move(eye);
    
    if (mShadersInput) {
        mShadersInput->InputViewMatrix(&mMatrix);
    }
    
}
    


}


