
#pragma once

#include <Render/LayerRenderer.h>
#include <Scene/Camera.h>

namespace ftr {

class SceneRenderer : public LayerRenderer
{
public:
    
    
    SceneRenderer(Camera& camera);
    virtual ~SceneRenderer();
    
    void Render(Layer &layer);
    
    void setFrame(const  glm::vec4& frame);
    
    
    void setMarkingBufferVisible(bool visible);
    void RenderMarkingContent(Layer &layer);
    
    const Camera& camera() const { return mCamera; }
    
private:
    bool mMarkingBufferVisible;
    
    void RenderMainContent(Layer &layer);
    
    glm::vec4 mFrame;
    Camera& mCamera;
    
};
    
}

