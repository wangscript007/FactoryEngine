
#include <Model/LineNode.h>

namespace ftr {

LineNode::LineNode(PointNode* startPoint, PointNode* endPoint)
    :mStartPoint(startPoint)
    ,mEndPoint(endPoint)
{}

#pragma mark - Instance


void LineNode::Render(RenderBundle& renderBundle)
{
    Node::Render(renderBundle);
    if (mStartPoint) {
        mStartPoint->Render(renderBundle);
    }
    if (mEndPoint) {
        mEndPoint->Render(renderBundle);
    }
    
    linePrimitive.mBegin = mStartPoint->mOrigin;
    linePrimitive.mEnd = mEndPoint->mOrigin;
    linePrimitive.color.set(1.0f, 1.0f, 1.0f);
    renderBundle.AddPrimitive(linePrimitive);
}

void LineNode::Transform(const Mat4& m4Transformation)
{
    mStartPoint->Transform(m4Transformation);
    mEndPoint->Transform(m4Transformation);
}
    
}



