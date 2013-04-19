
#include <Model/Face.h>
#include <Model/Line.h>
#include <Model/Point.h>
#include <Main/Log.h>

namespace ftr {

Face::Face()
{
    
}


void Face::Render()
{
    Node::Render();
    glDisable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_CULL_FACE);
    glBegin(GL_POLYGON);
    {
        glColor3f(0.5f,0.5f,0.5f);
        glNormal3f(0,-1,0);
        for(auto i = mPointsVector.begin(); i != mPointsVector.end(); ++i) {
            glVertex3f((*i)->mOrigin.mX, (*i)->mOrigin.mY, (*i)->mOrigin.mZ);
        }
    }
    glEnd();
    
}

#pragma mark - Instance

void Face::setSize(const Vec3 size)
{
    mSize = size;
}

void Face::setOrigin(const Vec3 origin)
{
    mOrigin = origin;
}


void Face::AddPoint(Point* pPoint)
{
    mPointsVector.push_back(pPoint);
}

void Face::AddLine(Line* line)
{
    mLinesVector.push_back(line);
    AddNode(line);
}
//
// Checks if point is int the same plane with face.
// Point is in same plane if any three points coordinate in same axes is the same.
//
bool Face::IsInFacePlane(Vec3 vec)
{
    return true;
}
//
// Checks point in the same plane intersection with face
//
bool Face::Contains(Vec3 vec)
{
    return false;
}
//
// Adds cut region to face, should divide into convex polygons
//
void Face::Cut(Face *cutFace)
{
    
}

void Face::Transform(Mat4& m4Transformation)
{
    for(auto i = mPointsVector.begin(); i != mPointsVector.end(); ++i) {
        (*i)->Transform(m4Transformation);
    }
}

}
