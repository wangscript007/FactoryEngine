

#include "FTCamera.h"
#include "FTLog.h"

FTCamera::FTCamera()
{
    Reset();
}

FTCamera::FTCamera(const O5Vec3 coords)
{
    FTCamera();
    mvCoords = coords;   
}

void FTCamera::Reset()
{
    mvRotated = mvMoved = O5Vec2(0.0f, 0.0f);
    mvCoords = O5Vec3(5.0f, 5.0f, 5.0f);
    mfZoomFactor = 1.0f;
    mprojectionMode = kFTProjectionModeProjection;
    mvRotated = O5Vec2(0.0f, 0.0f);
    mvMoved = O5Vec2(0.0f, 0.0f);
}

void FTCamera::Look()
{
    FTLog(kFTLogEnvinroment, "");
    SetProjectionMode(mprojectionMode);    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(mvCoords.m_fX, mvCoords.m_fY, mvCoords.m_fZ, 0, 0, 0, 0, 1, 0);
    glTranslatef(mvMoved.m_fX, mvMoved.m_fY, -mvMoved.m_fX);
    glRotatef(mvRotated.m_fX, 1, 0, -1);
    glRotatef(mvRotated.m_fY, 0, 1, 0);
    FTLog(kFTLogEnvinroment, "move: %f %f", mvMoved.m_fX, mvMoved.m_fY);
    FTLog(kFTLogEnvinroment, "rotate: %f %f", mvRotated.m_fX, mvRotated.m_fY);
    FTLog(kFTLogEnvinroment, "corrds: %f %f %f", mvCoords.m_fX, mvCoords.m_fY, mvCoords.m_fZ);
}

void FTCamera::MoveBy(const O5Vec2 deltaMove)
{
    mvMoved.m_fX += deltaMove.m_fX;
    mvMoved.m_fY += deltaMove.m_fY;
}

void FTCamera::RotateBy(const O5Vec2 deltaRotation)
{
    mvRotated.m_fX += deltaRotation.m_fX;
    mvRotated.m_fY += deltaRotation.m_fY;
    double ip;
    modf(mvRotated.m_fX/360, &ip);
    mvRotated.m_fX = mvRotated.m_fX - ip*360;
    modf(mvRotated.m_fY/360, &ip);
    mvRotated.m_fY = mvRotated.m_fY - ip*360;
}

void FTCamera::ZoomBy(const GLfloat times)
{
    mvCoords.m_fX *= times;
    mvCoords.m_fY *= times;
    mvCoords.m_fZ *= times;
    //mfZoomFactor *= times;
}

void FTCamera::SetProjectionMode(FTProjectionMode projectionMode)
{
    mprojectionMode = projectionMode;
    
    switch (projectionMode) {
        case kFTProjectionModeProjection:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-1, 1, -1, 1, 2.0f, 100.0); // is zFar is larger may crash       
            //glFrustum(-mfZoomFactor, mfZoomFactor, -mfZoomFactor, mfZoomFactor, 1.0f, 100.0); // is zFar is larger may crash       
            break;
        case kFTProjectionModeOrthographic:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-1, 1, -1, 1, 2.0f, 100.0); // is zFar is larger may crash       
            //glOrtho(-mfZoomFactor, mfZoomFactor, -mfZoomFactor, mfZoomFactor, 0.0f, 100.0); // is zFar is larger may crash       
            break;
    }
}




