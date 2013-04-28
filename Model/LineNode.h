
#pragma once

#include <Model/Node.h>
#include <Model/PointNode.h>

namespace ftr {

class LineNode : public Node
{
public:
    LineNode(PointNode* startPoint, PointNode* endPoint);
    virtual ~LineNode() {}
    
    virtual void Render(RenderBundle& renderBundle);
    virtual NodeType Type() const { return kLine; }
    void setEndPoint(PointNode* endPoint) { mEndPoint = endPoint; }
    void setStartPoint(PointNode* startPoint) { mStartPoint = startPoint; }
    PointNode* StartPoint() const { return mStartPoint; }
    PointNode* EndPoint() const { return mEndPoint; }
    virtual void Transform(const Mat4& m4Transformation);

private:
    LinePrimitive linePrimitive;
    PointNode* mStartPoint;
    PointNode* mEndPoint;
};

}