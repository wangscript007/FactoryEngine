
#include <Graph/LineNode.h>

namespace ftr {

LineNode::LineNode(PointNode* startPoint, PointNode* endPoint)
    :mStartPoint(startPoint)
    ,mEndPoint(endPoint)
{}

#pragma mark - Instance


void LineNode::Render(Layer& layer)
{
    if (mStartPoint && mEndPoint) {
        mStartPoint->Render(layer);
        mEndPoint->Render(layer);
        
        if (mInvalid) {
            mLinePrimitive.mBegin = mStartPoint->mOrigin;
            mLinePrimitive.mEnd = mEndPoint->mOrigin;
            mLinePrimitive.mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            mLinePrimitive.setOption(Primitive::kUseDepth, false);
        }
        layer.AddPrimitive(mLinePrimitive);
    }
    
    Node::Render(layer);
}
    
void LineNode::Invalidate(bool recursively)
{
    if (mInvalid) return;
    
    Node::Invalidate(recursively);
    mLinePrimitive.Invalidate();
    
    if (recursively) {
        mEndPoint->Invalidate(recursively);
        mStartPoint->Invalidate(recursively);
    }
}

void LineNode::Transform(const glm::mat4& m4Transformation)
{
    mStartPoint->Transform(m4Transformation);
    mEndPoint->Transform(m4Transformation);
}
    
void LineNode::PointNodes(std::vector<Node*>& result) const
{
    Node::PointNodes(result);
    result.push_back(mStartPoint);
    result.push_back(mEndPoint);
    
}
    

    
}



