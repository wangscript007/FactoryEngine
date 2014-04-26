
#pragma once

#include <Graph/Node.h>

namespace ftr {
    
class ModelEditor;
class PointNode;
class Picker;

class SelectInteraction : public Node
{
public:
    SelectInteraction(ModelEditor& modelEditor, const Viewport& viewport);
    virtual ~SelectInteraction();
    void Render(Layer& layer);
    
    void Select(const glm::vec2& point);    
    void TurnOn();
    void TurnOff();
private:
    
    ModelEditor& mModelEditor;
};
    
}

