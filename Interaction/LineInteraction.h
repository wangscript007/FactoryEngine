
#pragma once

#include <Model/Node.h>

namespace ftr {

class ModelManager;
class PointNode;

class LineInteraction : public Node
{
public:
    LineInteraction(ModelManager& modelManager);
    virtual ~LineInteraction() {}
    void Render(Layer& layer);
    void Begin();
    void Step();
    void End();
    void setStart(Vec3 start);
    void setEnd(Vec3 end);
    
private:
    ModelManager& mModelManager;
    Vec3 mStart;
    Vec3 mEnd;
    bool mActive;
    PointNode* mStartPoint;
    PointNode* mEndPoint;
    LinePrimitive linePrimitive;

};

}
