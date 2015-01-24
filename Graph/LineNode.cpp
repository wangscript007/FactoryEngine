
#include <Graph/LineNode.h>
#include <Graph/Edge.h>
#include <Graph/FaceNode.h>

namespace ftr {

LineNode::LineNode(PointNode* startPoint, PointNode* endPoint)
    :mStartPoint(startPoint)
    ,mEndPoint(endPoint)
    ,mEdge(NULL)
{}

#pragma mark - Instance


void LineNode::Render(Layer& layer)
{
    if (mStartPoint && mEndPoint) {
        mStartPoint->Render(layer);
        mEndPoint->Render(layer);
        
        if (mInvalid) {
            mLinePrimitive.mBegin = mStartPoint->Origin();
            mLinePrimitive.mEnd = mEndPoint->Origin();
            mLinePrimitive.mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
            mLinePrimitive.setOption(Primitive::kUseDepth, true);
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
    
    if (mEdge) {
        for (FaceNode* face : mEdge->mFaces) {
            face->Invalidate(false);
        }
    }
    
    if (recursively) {   
        mEndPoint->Invalidate(false);
        mStartPoint->Invalidate(false);
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



