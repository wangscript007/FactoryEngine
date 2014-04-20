
#pragma once

#include <Model/Node.h>
#include <Model/PointNode.h>

namespace ftr {

class LineNode : public Node
{
public:
    virtual NodeType Type() const { return kLine; }
    
    LineNode(PointNode* startPoint, PointNode* endPoint);
    virtual ~LineNode() {}
    
    virtual void Render(Layer& layer);
    
    void setEndPoint(PointNode* endPoint) { mEndPoint = endPoint; }
    void setStartPoint(PointNode* startPoint) { mStartPoint = startPoint; }
    PointNode* StartPoint() const { return mStartPoint; }
    PointNode* EndPoint() const { return mEndPoint; }
    virtual void Transform(const glm::mat4& m4Transformation);

private:
    LinePrimitive linePrimitive;
    PointNode* mStartPoint;
    PointNode* mEndPoint;
};

}