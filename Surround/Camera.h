
#pragma once

#include <Model/Node.h>
#include <Shading/ShadersInput.h>



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
    void LookAt(const Vec3& eye, const Vec3& center, const Vec3& up);
    
    Mat4* matrix() { return &mMatrix; }
    
    void setShadersInput(ShadersInput* shadersInput) { mShadersInput = shadersInput; }
    
private:
    Mat4 mMatrix;
    Mat4 mProjectionMatrix;
    ProjectionMode mProjectionMode;
    ShadersInput* mShadersInput;
};
    
}

