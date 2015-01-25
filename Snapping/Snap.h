
#pragma once

namespace ftr {
    
class Picker;
class ModelTree;
class Viewport;
    
class Snap
{
public:
    Snap(const Viewport& viewport, const Picker& picker, const ModelTree& modelTree);
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
    const Picker& mPicker;
    const ModelTree& mModelTree;
};
    
}

