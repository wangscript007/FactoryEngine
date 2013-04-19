// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/Point.h>
#include <Model/Face.h>
#include <Model/Line.h>

namespace ftr {

class ModelTreeManager;
//
// 
//
class ModelFactory
{
public:
    ModelFactory(ModelTreeManager& modelTreeManager);
    ~ModelFactory() {}
    
    Face*     CreateRectangle(const Vec3& origin, const Vec3& size) const;
    Face*     CreateCircle(Vec3 origin, float radius, int iCount) const;
    Face*     CreatePolygon(std::vector<Point*>& pointsVector) const;
    Face*     CreateFace(Vec3 origin, Vec3 size, Face::FaceType eType) const;
    Point*    CreatePoint(Vec3 origin) const;
    Line*     CreateLine(Point* startPoint, Point* endPoint) const;
    
private:
    ModelTreeManager& mModelTreeManager;
};

}