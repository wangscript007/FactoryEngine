
#pragma once

#include <Model/Node.h>
#include <Scene/Camera.h>
#include <Interaction/InteractionAssistant.h>
#include <Snapping/SnappingQueue.h>

namespace ftr {

class ModelEditor;
class PointNode;

class LineInteraction : public Node
{
public:
    LineInteraction(ModelEditor& modelEditor, const Viewport& viewport);
    virtual ~LineInteraction();
    void Render(Layer& layer);
    
    void Begin();
    void Step();
    void Finish();
    
    void setStart(const glm::vec2& start);
    void setEnd(const glm::vec2& end);
    
    const glm::vec3& start() const { return mStart; }
    const glm::vec3& end() const { return mEnd; }
    
private:
    glm::vec3 mStart;
    glm::vec3 mEnd;
    bool mActive;
    PointNode* mStartPoint;
    PointNode* mEndPoint;
    LinePrimitive linePrimitive;
    ModelEditor& mModelEditor;
    InteractionAssistant mInteractionAssitant;
    SnappingQueue* mSnappingQueue;
    
    std::vector<glm::vec3> mDebugPoints;
};

}
