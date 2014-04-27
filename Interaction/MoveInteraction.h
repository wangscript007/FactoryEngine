#pragma once

#include <Graph/Node.h>

namespace ftr {

class ModelEditor;

class MoveInteraction : public Node
{
public:
    MoveInteraction(ModelEditor& ModelEditor);
    virtual ~MoveInteraction() {}
    
    void Render(Layer &layer);
    
    void Select(const glm::vec2& startPoint);
    void MoveTo(const glm::vec2& targetPoint);
    
    void TurnOn();
    void TurnOff();
    
private:
    glm::vec2 mStart;
    glm::vec2 mTarget;
    
    Node* mSelectedNode;
    ModelEditor& mModelEditor;
    bool mActive;
};
    
}

