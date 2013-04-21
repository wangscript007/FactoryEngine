
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
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLineWidth(1);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    {
        Vec3 startVec = mStartPoint->mOrigin;
        Vec3 endVec = mEndPoint->mOrigin;
        glVertex3d(startVec.mX,
                   startVec.mY,
                   startVec.mZ);
        glVertex3d(endVec.mX,
                   endVec.mY,
                   endVec.mZ);
    }
    glEnd();
}

void LineNode::Transform(const Mat4& m4Transformation)
{
    mStartPoint->Transform(m4Transformation);
    mEndPoint->Transform(m4Transformation);
}
    
}



