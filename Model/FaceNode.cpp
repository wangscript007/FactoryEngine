
#include <Model/FaceNode.h>
#include <Model/LineNode.h>
#include <Model/PointNode.h>
#include <Main/Log.h>

namespace ftr {

FaceNode::FaceNode()
{
    
}


void FaceNode::Render(Layer& layer)
{
    Node::Render(layer);
    
}

#pragma mark - Instance

void FaceNode::setSize(const Vec3 size)
{
    mSize = size;
}

void FaceNode::setOrigin(const Vec3 origin)
{
    mOrigin = origin;
}


void FaceNode::AddPoint(PointNode* pPoint)
{
    mPointsVector.push_back(pPoint);
}

void FaceNode::AddLine(LineNode* line)
{
    mLinesVector.push_back(line);
    AddNode(line);
}
//
// Checks if point is int the same plane with face.
// PointNode is in same plane if any three points coordinate in same axes is the same.
//
bool FaceNode::IsInFacePlane(Vec3 vec)
{
    return true;
}
//
// Checks point in the same plane intersection with face
//
bool FaceNode::Contains(Vec3 vec)
{
    return false;
}
//
// Adds cut region to face, should divide into convex polygons
//
void FaceNode::Cut(FaceNode *cutFace)
{
    
}

void FaceNode::Transform(Mat4& m4Transformation)
{
    for(auto i = mPointsVector.begin(); i != mPointsVector.end(); ++i) {
        (*i)->Transform(m4Transformation);
    }
}

}
