// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/Point.h>
#include <Model/Face.h>
#include <Model/Line.h>

namespace Factory {

class ModelTreeManager;
//
// 
//
class ModelFactory
{
public:
    ModelFactory(ModelTreeManager& rModelTreeManager);
    ~ModelFactory() {}
    
    Face*     CreateRectangle(const Vec3& vOrigin, const Vec3& vSize) const;
    Face*     CreateCircle(Vec3 vOrigin, float fRadius, int iCount) const;
    Face*     CreatePolygon(std::vector<Point*>& vPointsVector) const;
    Face*     CreateFace(Vec3 vOrigin, Vec3 vSize, Face::FaceType eType) const;
    Point*    CreatePoint(Vec3 vOrigin) const;
    Line*     CreateLine(Point* pStartPoint, Point* pEndPoint) const;
    
private:
    ModelTreeManager& m_rModelTreeManager;
};

}