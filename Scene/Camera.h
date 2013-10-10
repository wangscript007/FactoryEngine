
#pragma once

#include <Model/Node.h>
#include <Shading/ShadingInterface.h>



namespace ftr {
    
typedef enum {
    kProjectionPerspective,
    kProjectionOrthographic
} Projection;

class Camera : public Node
{
public:
    typedef struct {
        glm::mat4 projectionMatrix;
        glm::mat4 modelviewMatrix;
         glm::vec4 viewport;
    } Parameters;
    
    static const float kViewportScale;
    
    Camera(const glm::vec3& eyePosition);
    
    void MoveBy(const glm::vec2 deltaMove);
    void RotateBy(const glm::vec2 deltaRotation);
    void ZoomBy(const GLfloat times);
    
    void CreateTransformations();
    
    void setProjection(Projection projectionMode);
    void setShadingInterface(ShadingInterface* ShadingInterface) { mShadingInterface = ShadingInterface; }
    void setViewport(const  glm::vec4& frame);
    const Parameters& getParameters() const { return mParameters; };
    void CommitTransformations();
    
private:
    glm::vec3 mEyePosition;
    glm::vec3 mTranslation;
    glm::vec3 mRotation;
    Projection mProjection;
    Parameters mParameters;
    glm::mat4 mModelviewMatrix;
    
    ShadingInterface* mShadingInterface;
    ShadingInterface::Transform mTransform;
};
    
}

