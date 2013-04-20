// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Model/ModelFactory.h>
#include <Model/Point.h>
#include <Model/ModelTreeManager.h>

namespace ftr {

ModelFactory::ModelFactory(ModelTreeManager& modelTreeManager)
    :mModelTreeManager(modelTreeManager)
{
    
}

Face* ModelFactory::CreateRectangle(const Vec3& origin, const Vec3& size) const
{
    std::vector<Point*> pointsVector;
    pointsVector.push_back(new Point(Vec3(origin.mX, origin.mY, origin.mZ)));
    pointsVector.push_back(new Point(Vec3(origin.mX + size.mX, origin.mY, origin.mZ)));
    pointsVector.push_back(new Point(Vec3(origin.mX + size.mX, origin.mY, origin.mZ + size.mZ)));
    pointsVector.push_back(new Point(Vec3(origin.mX, origin.mY, origin.mZ + size.mZ)));
    return CreatePolygon(pointsVector);
}

Face* ModelFactory::CreateCircle(Vec3 origin, float radius, int iCount) const
{
    Point* pPoint;
    std::vector<Point*> pointsVector;
    float radAngleStep = M_2_PI/((float)iCount);
    float radAngle = 0;
    float x, y;
    float z = origin.mZ;
    for(int i = 0; i < iCount; i++) {
        radAngle += radAngleStep;
        x = radius*cosf(radAngle);
        y = radius*sinf(radAngle);
        pPoint = new Point();
        pPoint->mOrigin = Vec3(x, y, z);
        pointsVector.push_back(pPoint);
    }
    return CreatePolygon(pointsVector);
}

Face* ModelFactory::CreatePolygon(std::vector<Point*>& pointsVector) const
{
    Face* pFace = new Face();
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

Face* ModelFactory::CreateFace(Vec3 origin, Vec3 size, Face::FaceType eType) const
{
    switch (eType) {
        case Face::kRectangle : {
            Face* pFace = new Face();
            pFace->m_eType = Face::kRectangle;
            pFace->setOrigin(origin);
            pFace->setSize(size);
            return pFace;
        } break;
        default: assert(false); break;
    }
    return NULL;
}

Point* ModelFactory::CreatePoint(Vec3 origin) const
{
    Point* pPoint = new Point();
    pPoint->mOrigin = origin;
    return pPoint;
}

Line* ModelFactory::CreateLine(Point* startPoint, Point* endPoint) const
{
    Line* line = new Line(startPoint, endPoint);
    return line;
}

}