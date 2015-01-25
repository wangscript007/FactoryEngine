
#pragma once

namespace ftr {

class ColorPickingMapper;
class ModelTree;
class Node;
class SceneRenderer;
class Layer;
    
class Picker
{
public:
    Picker(ModelTree& modelTree, SceneRenderer& sceneRenderer, Layer& layer);
    virtual ~Picker();
    
    Node* PickNode(const glm::vec2& atPoint) const;
    glm::vec3 PickSceneCoordinates(const glm::vec2& atPoint) const;
    
    bool isOn() const { return mIsOn; }
    void setOn(bool on);
    
private:
    ColorPickingMapper* mColorPickingMapper;
    ModelTree& mModelTree;
    SceneRenderer& mSceneRenderer;
    Layer& mLayer;
    bool mIsOn;

};
    
}

