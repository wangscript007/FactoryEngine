#pragma once

#include <Graph/Node.h>

namespace ftr {

class ModelEditor;
class Camera;
class Triangle;

class MoveInteraction : public Node
{
public:
    MoveInteraction(ModelEditor& ModelEditor, const Viewport& viewport);
    virtual ~MoveInteraction() {}
    
    void Render(Layer &layer);
    
    void Select(const glm::vec2& startPoint);
    void Select(Node* node);
    void MoveTo(const glm::vec2& targetPoint);
    
    void TurnOn();
    void TurnOff();
    
private:
    
    glm::vec2 mStart;
    glm::vec2 mTarget;
    
    Node* mSelectedNode;
    ModelEditor& mModelEditor;
    const Viewport& mViewport;
    bool mActive;
};
    
}

