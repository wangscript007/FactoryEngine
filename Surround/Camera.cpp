

#include <Surround/Camera.h>
#include <Main/Log.h>
#include <Math/Transformation.h>


namespace ftr {

Camera::Camera()
{
    Reset();
}

Camera::Camera(const Vec3 coords)
{
    Camera();
}

void Camera::Reset()
{
    
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    mMatrix *= Transformation::Move(Vec3(deltaMove.mX, deltaMove.mY, -deltaMove.mX));
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    mMatrix *= Transformation::Rotate(Vec3(deltaRotation.mX, deltaRotation.mY, 0.0));
}

void Camera::ZoomBy(const GLfloat times)
{
    mMatrix *= Mat4::Identity*times;
}

void Camera::setProjectionMode(ProjectionMode projectionMode)
{
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
    
void Camera::Projection(float fov, float ratio, float nearP, float farP)
{
    /*
    mProjectionMatrix.Identity;
    float f = 1.0f / tan (fov * (M_PI / 360.0));
    setIdentityMatrix(mat,4);
    
    mat[0] = f / ratio;
    mat[1 * 4 + 1] = f;
    mat[2 * 4 + 2] = (farP + nearP) / (nearP - farP);
    mat[3 * 4 + 2] = (2.0f * farP * nearP) / (nearP - farP);
    mat[2 * 4 + 3] = -1.0f;
    mat[3 * 4 + 3] = 0.0f;
    */
}
    
void Camera::Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
{
    mProjectionMatrix = Mat4::Identity;
    mProjectionMatrix[0][0] = 2*near/(right - left);
    mProjectionMatrix[1][1] = 2*near/(top - bottom);
    mProjectionMatrix[0][2] = (right + left)/(right - left); // A
    mProjectionMatrix[1][2] = (top + bottom)/(top - bottom); // B
    mProjectionMatrix[2][2] = (far + near)/(far - near); // C
    mProjectionMatrix[2][3] = (2*far*near)/(far - near); // D
    mProjectionMatrix[3][2] = -1;
    mProjectionMatrix[3][3] = 0;
}
    
void Camera::Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far)
{
    
}

}


