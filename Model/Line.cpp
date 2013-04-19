
#include <Model/Line.h>

namespace ftr {

Line::Line(Point* startPoint, Point* endPoint)
    :mStartPoint(startPoint)
    ,mEndPoint(endPoint)
{}

#pragma mark - Instance


void Line::Render()
{
    Node::Render();
    if (mStartPoint) {
        mStartPoint->Render();
    }
    if (mEndPoint) {
        mEndPoint->Render();
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

void Line::Transform(const Mat4& m4Transformation)
{
    mStartPoint->Transform(m4Transformation);
    mEndPoint->Transform(m4Transformation);
}
    
}



