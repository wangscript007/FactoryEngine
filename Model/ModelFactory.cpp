// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Model/ModelFactory.h>
#include <Model/PointNode.h>
#include <Model/ModelTreeManager.h>

namespace ftr {

ModelFactory::ModelFactory(ModelTreeManager& modelTreeManager)
    :mModelTreeManager(modelTreeManager)
{
    
}

FaceNode* ModelFactory::CreateRectangle(const Vec3& origin, const Vec3& size) const
{
    std::vector<PointNode*> pointsVector;
    pointsVector.push_back(new PointNode(Vec3(origin.mX, origin.mY, origin.mZ)));
    pointsVector.push_back(new PointNode(Vec3(origin.mX + size.mX, origin.mY, origin.mZ)));
    pointsVector.push_back(new PointNode(Vec3(origin.mX + size.mX, origin.mY, origin.mZ + size.mZ)));
    pointsVector.push_back(new PointNode(Vec3(origin.mX, origin.mY, origin.mZ + size.mZ)));
    return CreatePolygon(pointsVector);
}

FaceNode* ModelFactory::CreateCircle(Vec3 origin, float radius, int iCount) const
{
    PointNode* pPoint;
    std::vector<PointNode*> pointsVector;
    float radAngleStep = M_2_PI/((float)iCount);
    float radAngle = 0;
    float x, y;
    float z = origin.mZ;
    for(int i = 0; i < iCount; i++) {
        radAngle += radAngleStep;
        x = radius*cosf(radAngle);
        y = radius*sinf(radAngle);
        pPoint = new PointNode();
        pPoint->mOrigin = Vec3(x, y, z);
        pointsVector.push_back(pPoint);
    }
    return CreatePolygon(pointsVector);
}

FaceNode* ModelFactory::CreatePolygon(std::vector<PointNode*>& pointsVector) const
{
    FaceNode* pFace = new FaceNode();
    for(int i = 0; i < pointsVector.size(); i++) {
        pFace->AddPoint(pointsVector[i]);
        if (i > 0) {
            pFace->AddLine(CreateLine(pointsVector[i], pointsVector[i-1]));
        }
    }
    // Closing line
    size_t size = pointsVector.size();
    pFace->AddLine(CreateLine(pointsVector[size-1], pointsVector[0]));
    return pFace;
}

FaceNode* ModelFactory::CreateFace(Vec3 origin, Vec3 size, FaceNode::FaceType eType) const
{
    switch (eType) {
        case FaceNode::kRectangle : {
            FaceNode* pFace = new FaceNode();
            pFace->m_eType = FaceNode::kRectangle;
            pFace->setOrigin(origin);
            pFace->setSize(size);
            return pFace;
        } break;
        default: assert(false); break;
    }
    return NULL;
}

PointNode* ModelFactory::CreatePoint(Vec3 origin) const
{
    PointNode* pPoint = new PointNode();
    pPoint->mOrigin = origin;
    return pPoint;
}

LineNode* ModelFactory::CreateLine(PointNode* startPoint, PointNode* endPoint) const
{
    LineNode* line = new LineNode(startPoint, endPoint);
    return line;
}

}