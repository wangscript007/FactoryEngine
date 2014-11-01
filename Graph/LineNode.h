
#pragma once

#include <Graph/Node.h>
#include <Graph/PointNode.h>

namespace ftr {

class LineNode : public Node
{
public:
    virtual enum Type Type() const { return kLine; }
    
    LineNode(PointNode* startPoint, PointNode* endPoint);
    virtual ~LineNode() {}
    
    void Render(Layer& layer);
    void Invalidate(bool recursively);
    
    void setEndPoint(PointNode* endPoint) { mEndPoint = endPoint; }
    void setStartPoint(PointNode* startPoint) { mStartPoint = startPoint; }
    PointNode* StartPoint() const { return mStartPoint; }
    PointNode* EndPoint() const { return mEndPoint; }
    virtual void Transform(const glm::mat4& m4Transformation);

private:
    LinePrimitive mLinePrimitive;
    PointNode* mStartPoint;
    PointNode* mEndPoint;
};

}