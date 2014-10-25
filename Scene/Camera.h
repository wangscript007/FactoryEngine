
#pragma once

#include <Graph/Node.h>
#include <Shading/ShadingInterface.h>
#include <Scene/Viewport.h>


namespace ftr {
    
class Triangle;
    
typedef enum {
    kProjectionPerspective,
    kProjectionOrthographic
} Projection;

class Camera : public Node
{
public:
    
    static const float kViewportScale;
    
    Camera(Viewport& viewport);
    
    void MoveBy(const glm::vec2 deltaMove);
    void RotateBy(const glm::vec2 deltaRotation);
    void ZoomBy(const float delta, const glm::vec2& toViewportPoint);
    
    void CreateTransformations();
    
    void setProjection(Projection projectionMode);
    void setShadingInterface(ShadingInterface* ShadingInterface) { mShadingInterface = ShadingInterface; }
    void setViewport(const  glm::vec4& frame);
    const Viewport& viewport() const { return mViewport; }
    void CommitTransformations();
    
private:
    glm::vec3 RotateVector(const glm::vec3& vec) const;
    glm::mat4 RotationMatrix();
    glm::mat4 TranslationMatrix();
    glm::mat4 InitialMatrix();
    
    glm::vec3 mEyePosition;
    glm::vec3 mTranslation;
    glm::vec3 mRotation;
    Projection mProjection;
    glm::vec3 mPivot;
    
    Viewport& mViewport;
    ShadingInterface* mShadingInterface;
};
    
}

