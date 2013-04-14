
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
                        Camera(const Vec3 coords);
    void                MoveBy(const Vec2 deltaMove);
    void                RotateBy(const Vec2 deltaRotation);
    void                ZoomBy(const GLfloat times);
    void                Look();
    void                SetProjectionMode(ProjectionMode projectionMode);
    void                Reset();
private:
    Vec2              mvRotated;
    Vec2              mvMoved;
    Vec3              mvCoords;
    ProjectionMode    mprojectionMode;
    GLdouble            mfZoomFactor;
};
    
}

