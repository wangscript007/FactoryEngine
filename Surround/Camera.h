
#pragma once

#include <Model/Node.h>



namespace ftr {

typedef enum {
    kProjectionModeProjection,
    kProjectionModeOrthographic
} ProjectionMode;

class Camera : public Node
{
public:
    Camera();
    Camera(const Vec3 coords);
    
    void MoveBy(const Vec2 deltaMove);
    void RotateBy(const Vec2 deltaRotation);
    void ZoomBy(const GLfloat times);
    void Look();
    void Reset();
    
    void setProjectionMode(ProjectionMode projectionMode);
    
private:
    Vec2 mRotated;
    Vec2 mMoved;
    Vec3 mCoords;
    ProjectionMode mProjectionMode;
    GLdouble mZoomFactor;
};
    
}

