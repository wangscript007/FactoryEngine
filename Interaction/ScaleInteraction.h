#pragma once

#include <Graph/Node.h>

namespace ftr {

class ModelEditor;

class ScaleInteraction : public Node
{
public:
    ScaleInteraction(ModelEditor& ModelEditor);
    virtual ~ScaleInteraction() {}
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
