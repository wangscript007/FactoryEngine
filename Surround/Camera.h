
#pragma once

#include <Model/Model.h>



namespace Factory {

typedef enum {
    kProjectionModeProjection,
    kProjectionModeOrthographic
} ProjectionMode;

class Camera : public Model
{
public:
                        Camera();
                        Camera(const O5Vec3 coords);
    void                MoveBy(const O5Vec2 deltaMove);
    void                RotateBy(const O5Vec2 deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                SetProjectionMode(ProjectionMode projectionMode);
    void                Reset();
private:
    O5Vec2              mvRotated;
    O5Vec2              mvMoved;
    O5Vec3              mvCoords;
    ProjectionMode    mprojectionMode;
    GLdouble            mfZoomFactor;
};
    
}

