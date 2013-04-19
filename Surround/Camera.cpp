

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
    
    gluLookAt(mCoords.m_fX, mCoords.m_fY, mCoords.m_fZ, 0, 0, 0, 0, 1, 0);
    glTranslatef(mMoved.m_fX, mMoved.m_fY, -mMoved.m_fX);
    glRotatef(mRotated.m_fX, 1, 0, -1);
    glRotatef(mRotated.m_fY, 0, 1, 0);
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    mMoved.m_fX += deltaMove.m_fX;
    mMoved.m_fY += deltaMove.m_fY;
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    mRotated.m_fX += deltaRotation.m_fX;
    mRotated.m_fY += deltaRotation.m_fY;
    double ip;
    modf(mRotated.m_fX/360, &ip);
    mRotated.m_fX = mRotated.m_fX - ip*360;
    modf(mRotated.m_fY/360, &ip);
    mRotated.m_fY = mRotated.m_fY - ip*360;
}

void Camera::ZoomBy(const GLfloat times)
{
    mCoords.m_fX *= times;
    mCoords.m_fY *= times;
    mCoords.m_fZ *= times;
}

void Camera::setProjectionMode(ProjectionMode projectionMode)
{
    mProjectionMode = projectionMode;
    
    switch (projectionMode) {
        case kProjectionModeProjection:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-1, 1, -1, 1, 2.0f, 100.0); 
            break;
        case kProjectionModeOrthographic:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-5, 1, -1, 1, 2.0f, 100.0);
            break;
    }
}

}


