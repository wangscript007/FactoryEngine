
#include <Model/Point.h>
#include <Main/Log.h>


namespace ftr {

const float Point::c_fR = 5.0f;


Point::Point()
    :mOctreeLeaf(NULL)
    ,mIsActive(false)
{
    
}

Point::Point(Vec3 origin)
:mOrigin(origin)
{
    Point();
}

void Point::Transform(const Mat4& m4Transformation)
{
    mOrigin *= m4Transformation;
    Log(kLogModel, "[%f, %f, %f]", mOrigin.mX, mOrigin.mY, mOrigin.mZ);
}

#pragma mark - Instance

//
// Renders cicle at point position
//
void Point::Render()
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

