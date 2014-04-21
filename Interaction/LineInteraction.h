
#pragma once

#include <Graph/Node.h>
#include <Scene/Camera.h>
#include <Snapping/SnappingQueue.h>
#include <Snapping/PointSnap.h>

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
    SnappingQueue* mSnappingQueue;
    PointSnap* mPointSnap;
    const Viewport* mViewport;
    
    std::vector<glm::vec3> mDebugPoints;
};

}
