
#pragma once

#include <Model/Node.h>



namespace ftr {
typedef enum {
    kProjectionModeProjection,
    kProjectionModeOrthographic
} ProjectionMode;

//
// Edits camera matrix
//
class Camera : public Node
{
public:
    Camera();
    Camera(const Vec3 coords);
    
    void MoveBy(const Vec2 deltaMove);
    void RotateBy(const Vec2 deltaRotation);
    void ZoomBy(const GLfloat times);
    void Reset();
    void setProjectionMode(ProjectionMode projectionMode);
    void Projection(float fov, float ratio, float nearP, float farP);
    void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);
    void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near, GLdouble far);
    const Mat4* matrix();
    
private:
    Mat4 mMatrix;
    Mat4 mProjectionMatrix;
    ProjectionMode mProjectionMode;
};
    
}

