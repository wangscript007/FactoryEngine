
#include <Graph/LineNode.h>

namespace ftr {

LineNode::LineNode(PointNode* startPoint, PointNode* endPoint)
    :mStartPoint(startPoint)
    ,mEndPoint(endPoint)
{}

#pragma mark - Instance


void LineNode::Render(Layer& layer)
{
    Node::Render(layer);
    if (mStartPoint && mEndPoint) {
        mStartPoint->Render(layer);
        mEndPoint->Render(layer);
        
        mLinePrimitive.mBegin = mStartPoint->mOrigin;
        mLinePrimitive.mEnd = mEndPoint->mOrigin;
        mLinePrimitive.mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        mLinePrimitive.setOption(Primitive::kUseDepth, false);
        layer.AddPrimitive(mLinePrimitive);
    }
    
}
    
void LineNode::Invalidate()
{
    Node::Invalidate();
    mLinePrimitive.Invalidate();
}

void LineNode::Transform(const glm::mat4& m4Transformation)
{
    mStartPoint->Transform(m4Transformation);
    mEndPoint->Transform(m4Transformation);
}
    

    
}



