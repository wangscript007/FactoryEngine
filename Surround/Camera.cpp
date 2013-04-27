

#include <Surround/Camera.h>
#include <Main/Log.h>

namespace ftr {

Camera::Camera()
{
    Reset();
}

Camera::Camera(const Vec3 coords)
{
    Camera();
    mCoords = coords;   
}

void Camera::Reset()
{
    mRotated = mMoved = Vec2(0.0f, 0.0f);
    mCoords = Vec3(5.0f, 5.0f, 5.0f);
    mZoomFactor = 1.0f;
    mProjectionMode = kProjectionModeProjection;
    mRotated = Vec2(0.0f, 0.0f);
    mMoved = Vec2(0.0f, 0.0f);
}

void Camera::Look()
{
    setProjectionMode(mProjectionMode);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(mCoords.mX, mCoords.mY, mCoords.mZ, 0, 0, 0, 0, 1, 0);
    glTranslatef(mMoved.mX, mMoved.mY, -mMoved.mX);
    glRotatef(mRotated.mX, 1, 0, -1);
    glRotatef(mRotated.mY, 0, 1, 0);
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    mMoved.mX += deltaMove.mX;
    mMoved.mY += deltaMove.mY;
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    mRotated.mX += deltaRotation.mX;
    mRotated.mY += deltaRotation.mY;
    double ip;
    modf(mRotated.mX/360, &ip);
    mRotated.mX = mRotated.mX - ip*360;
    modf(mRotated.mY/360, &ip);
    mRotated.mY = mRotated.mY - ip*360;
}

void Camera::ZoomBy(const GLfloat times)
{
    mCoords.mX *= times;
    mCoords.mY *= times;
    mCoords.mZ *= times;
}

void Camera::setProjectionMode(ProjectionMode projectionMode)
{
    mProjectionMode = projectionMode;
    switch (projectionMode) {
        case kProjectionModeProjection:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-1, 1, -1, 1, 2.0f, 2000.0);
            break;
        case kProjectionModeOrthographic:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-5, 1, -1, 1, 2.0f, 2000.0);
            break;
    }
}

}


