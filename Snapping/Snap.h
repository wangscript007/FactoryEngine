
#pragma once

#include <Scene/Viewport.h>
#include <Model/ModelTree.h>

namespace ftr {
    
class Snap
{
public:
    Snap(const Viewport& viewport, const ModelTree& modelTree);
    virtual ~Snap() {}
    
    void setStartScene(const glm::vec3& startScene, bool assignViewport = false);
    void setEndScene(const glm::vec3& endScene, bool assignViewport = false);
    
    void setStartViewport(const glm::vec2& startViewport, bool assignScene = false);
    void setEndViewport(const glm::vec2& endViewport, bool assignScene = false);
    
    virtual glm::vec3 Snapped() const { return glm::vec3(0.0f); }
    
protected:
    glm::vec3 mStartScene;
    glm::vec3 mEndScene;
    
    glm::vec2 mStartViewport;
    glm::vec2 mEndViewport;
    
    const Viewport& mViewport;
    const ModelTree& mModelTree;
};
    
}

