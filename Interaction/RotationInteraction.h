#pragma once

#include <Model/Node.h>

namespace ftr {

class ModelEditor;

class RotationInteraction : public Node
{
public:
    RotationInteraction(ModelEditor& ModelEditor);
    virtual ~RotationInteraction() {}
    void Render();
    
    void setStart(glm::vec3 start);
    void setEnd(glm::vec3 end);
    
private:
    glm::vec3 mStart;
    glm::vec3 mEnd;
    Node* mNode;
    ModelEditor& mModelEditor;
    bool mActive;
};

}
