
#pragma once

#include <Model/FTModel.h>

typedef enum {
    kFTProjectionModeProjection,
    kFTProjectionModeOrthographic
} FTProjectionMode;

class FTCamera : public FTModel
{
public:
                        FTCamera();
                        FTCamera(const O5Vec3 coords);
    void                MoveBy(const O5Vec2 deltaMove);
    void                RotateBy(const O5Vec2 deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                SetProjectionMode(FTProjectionMode projectionMode);
    void                Reset();
private:
    O5Vec2              mvRotated;
    O5Vec2              mvMoved;
    O5Vec3              mvCoords;
    FTProjectionMode    mprojectionMode;
    GLdouble            mfZoomFactor;
};

