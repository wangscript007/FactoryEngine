
#pragma once

#include <Model/Node.h>
#include <Scene/Camera.h>
#include <Interaction/InteractionAssistant.h>

namespace ftr {

class ModelEditor;
class PointNode;

class LineInteraction : public Node
{
public:
    LineInteraction(ModelEditor& ModelEditor);
    virtual ~LineInteraction() {}
    void Render(Layer& layer);
    void Begin();
    void Step();
    void End();
    void setStart(glm::vec3 start);
    void setEnd(glm::vec3 end);
    void setEndViewport(const glm::vec2& endViewport, const Camera::Parameters& cameraParameters);
    
private:
    ModelEditor& mModelEditor;
    glm::vec3 mStart;
    glm::vec3 mEnd;
    bool mActive;
    PointNode* mStartPoint;
    PointNode* mEndPoint;
    LinePrimitive linePrimitive;
    InteractionAssistant mInteractionAssitant;

};

}
