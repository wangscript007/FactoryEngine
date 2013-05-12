
#pragma once

#include <Model/Node.h>
#include <Shading/ShadersInput.h>



namespace ftr {
    
typedef enum {
    kProjectionPerspective,
    kProjectionOrthographic
} Projection;

class Camera : public Node
{
public:
    static const float kViewportScale;
    
    Camera(const Vec3& eyePosition);
    
    void MoveBy(const Vec2 deltaMove);
    void RotateBy(const Vec2 deltaRotation);
    void ZoomBy(const GLfloat times);
    
    void Look();
    
    void setProjection(Projection projectionMode);
    void setShadersInput(ShadersInput* shadersInput) { mShadersInput = shadersInput; }
    void setViewport(const Frame& frame);
    
private:
    Vec3 mEyePosition;
    Vec3 mTranslation;
    Vec3 mRotation;
    
    Mat4 mModelMatrix;
    Mat4 mProjectionMatrix;
    Mat4 mRotationMatrix;
    Mat4 mTranslationMatrix;
    
    Projection mProjection;
    ShadersInput* mShadersInput;
};
    
}

