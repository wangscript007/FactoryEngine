
#include <Model/PointNode.h>
#include <Main/Log.h>


namespace ftr {

const float PointNode::c_fR = 5.0f;


PointNode::PointNode()
    :mOctreeLeaf(NULL)
    ,mIsActive(false)
{
    
}

PointNode::PointNode(Vec3 origin)
:mOrigin(origin)
{
    PointNode();
}

void PointNode::Transform(const Mat4& m4Transformation)
{
    mOrigin *= m4Transformation;
    Log(kLogModel, "[%f, %f, %f]", mOrigin.mX, mOrigin.mY, mOrigin.mZ);
}

#pragma mark - Instance

//
// Renders cicle at point position
//
void PointNode::Render()
{
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPointSize(c_fR);
    
    glBegin(GL_POINTS);
    {
        if (mIsActive) {
            glColor3f(0.5f, 0.207, 0.031f);
        } else {
            glColor3f(0.95f, 0.207, 0.031f);
        }
        
        glVertex3f(mOrigin.mX, mOrigin.mY, mOrigin.mZ);
    }
    glEnd();
}
    
}

