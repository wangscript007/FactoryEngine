
#pragma once

#include <Graph/Node.h>

namespace ftr {
    
class ModelEditor;
class PointNode;

class SelectInteraction : public Node
{
public:
    SelectInteraction(ModelEditor& modelEditor, const Viewport& viewport);
    virtual ~SelectInteraction();
    void Render(Layer& layer);
    
    void Begin();
    void Step();
    void Finish();
    
    const glm::vec3& start() const { return mStart; }
    const glm::vec3& end() const { return mEnd; }
    
private:
    glm::vec3 mStart;
    glm::vec3 mEnd;
    bool mActive;
    
    ModelEditor& mModelEditor;
};
    
}

