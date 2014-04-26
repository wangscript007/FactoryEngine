
#pragma once

namespace ftr {

class ColorPickingMapper;
class ModelTree;
class Node;
class SceneRenderer;
    
class Picker
{
public:
    Picker(ModelTree& modelTree, SceneRenderer& sceneRenderer);
    virtual ~Picker();
    
    Node* Pick(const glm::vec2& atPoint);
    
    bool isOn() const { return mIsOn; }
    void setOn(bool on);
    
private:
    ColorPickingMapper* mColorPickingMapper;
    ModelTree& mModelTree;
    SceneRenderer& mSceneRenderer;
    bool mIsOn;

};
    
}

