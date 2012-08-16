

#include <FactoryEngine.h>

FTCamera::FTCamera()
{
    Reset();
}

FTCamera::FTCamera(const FTVec3f coords)
{
    FTCamera();
    mvCoords = coords;   
}

void FTCamera::Reset()
{
    mvRotated = mvMoved = FTMakeVec2f(0.0f, 0.0f);
    mvCoords = FTMakeVec3f(5.0f, 5.0f, 5.0f);
    mfZoomFactor = 1.0f;
    mprojectionMode = kFTProjectionModeProjection;
    mvRotated = FTMakeVec2f(0.0f, 0.0f);
    mvMoved = FTMakeVec2f(0.0f, 0.0f);
}

void FTCamera::Look()
{
    FTLog(kFTLogEnvinroment, "");
    SetProjectionMode(mprojectionMode);    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(mvCoords.x, mvCoords.y, mvCoords.z, 0, 0, 0, 0, 1, 0);
    glTranslatef(mvMoved.x, mvMoved.y, -mvMoved.x);
    glRotatef(mvRotated.x, 1, 0, -1);
    glRotatef(mvRotated.y, 0, 1, 0);
    FTLog(kFTLogEnvinroment, "move: %f %f", mvMoved.x, mvMoved.y);
    FTLog(kFTLogEnvinroment, "rotate: %f %f", mvRotated.x, mvRotated.y);
    FTLog(kFTLogEnvinroment, "corrds: %f %f %f", mvCoords.x, mvCoords.y, mvCoords.z);
}

void FTCamera::MoveBy(const FTVec2f deltaMove)
{
    mvMoved.x += deltaMove.x;
    mvMoved.y += deltaMove.y;
}

void FTCamera::RotateBy(const FTVec2f deltaRotation)
{
    mvRotated.x += deltaRotation.x;
    mvRotated.y += deltaRotation.y;
    double ip;
    modf(mvRotated.x/360, &ip);
    mvRotated.x = mvRotated.x - ip*360;
    modf(mvRotated.y/360, &ip);
    mvRotated.y = mvRotated.y - ip*360;
}

void FTCamera::ZoomBy(const GLfloat times)
{
    mvCoords.x *= times;
    mvCoords.y *= times;
    mvCoords.z *= times;
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




