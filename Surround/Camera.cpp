

#include <Surround/Camera.h>
#include <Main/Log.h>

namespace Factory {

Camera::Camera()
{
    Reset();
}

Camera::Camera(const Vec3 coords)
{
    Camera();
    mvCoords = coords;   
}

void Camera::Reset()
{
    mvRotated = mvMoved = Vec2(0.0f, 0.0f);
    mvCoords = Vec3(5.0f, 5.0f, 5.0f);
    mfZoomFactor = 1.0f;
    mprojectionMode = kProjectionModeProjection;
    mvRotated = Vec2(0.0f, 0.0f);
    mvMoved = Vec2(0.0f, 0.0f);
}

void Camera::Look()
{
    Log(kLogEnvinroment, "");
    SetProjectionMode(mprojectionMode);    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(mvCoords.m_fX, mvCoords.m_fY, mvCoords.m_fZ, 0, 0, 0, 0, 1, 0);
    glTranslatef(mvMoved.m_fX, mvMoved.m_fY, -mvMoved.m_fX);
    glRotatef(mvRotated.m_fX, 1, 0, -1);
    glRotatef(mvRotated.m_fY, 0, 1, 0);
    Log(kLogEnvinroment, "move: %f %f", mvMoved.m_fX, mvMoved.m_fY);
    Log(kLogEnvinroment, "rotate: %f %f", mvRotated.m_fX, mvRotated.m_fY);
    Log(kLogEnvinroment, "corrds: %f %f %f", mvCoords.m_fX, mvCoords.m_fY, mvCoords.m_fZ);
}

void Camera::MoveBy(const Vec2 deltaMove)
{
    mvMoved.m_fX += deltaMove.m_fX;
    mvMoved.m_fY += deltaMove.m_fY;
}

void Camera::RotateBy(const Vec2 deltaRotation)
{
    mvRotated.m_fX += deltaRotation.m_fX;
    mvRotated.m_fY += deltaRotation.m_fY;
    double ip;
    modf(mvRotated.m_fX/360, &ip);
    mvRotated.m_fX = mvRotated.m_fX - ip*360;
    modf(mvRotated.m_fY/360, &ip);
    mvRotated.m_fY = mvRotated.m_fY - ip*360;
}

void Camera::ZoomBy(const GLfloat times)
{
    mvCoords.m_fX *= times;
    mvCoords.m_fY *= times;
    mvCoords.m_fZ *= times;
    //mfZoomFactor *= times;
}

void Camera::SetProjectionMode(ProjectionMode projectionMode)
{
    mprojectionMode = projectionMode;
    
    switch (projectionMode) {
        case kProjectionModeProjection:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-1, 1, -1, 1, 2.0f, 100.0); // is zFar is larger may crash       
            //glFrustum(-mfZoomFactor, mfZoomFactor, -mfZoomFactor, mfZoomFactor, 1.0f, 100.0); // is zFar is larger may crash       
            break;
        case kProjectionModeOrthographic:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-5, 1, -1, 1, 2.0f, 100.0); // is zFar is larger may crash
            //glOrtho(-mfZoomFactor, mfZoomFactor, -mfZoomFactor, mfZoomFactor, 0.0f, 100.0); // is zFar is larger may crash       
            break;
    }
}

}


