
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
    typedef struct {
        Mat4 projectionMatrix;
        Mat4 modelviewMatrix;
        Frame viewport;
    } Parameters;
    
    static const float kViewportScale;
    
    Camera(const Vec3& eyePosition);
    
    void MoveBy(const Vec2 deltaMove);
    void RotateBy(const Vec2 deltaRotation);
    void ZoomBy(const GLfloat times);
    
    void Look();
    
    void setProjection(Projection projectionMode);
    void setShadersInput(ShadersInput* shadersInput) { mShadersInput = shadersInput; }
    void setViewport(const Frame& frame);
    const Parameters& getParameters() const { return mParameters; };
    
private:
    Vec3 mEyePosition;
    Vec3 mTranslation;
    Vec3 mRotation;
        
    Projection mProjection;
    Parameters mParameters;
    Mat4 mModelviewMatrix;
    
    ShadersInput* mShadersInput;
    ShadersInput::Transform mTransform;
};
    
}

