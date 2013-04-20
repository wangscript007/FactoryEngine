// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/PointNode.h>
#include <Model/FaceNode.h>
#include <Model/LineNode.h>

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
    
    FaceNode*     CreateRectangle(const Vec3& origin, const Vec3& size) const;
    FaceNode*     CreateCircle(Vec3 origin, float radius, int iCount) const;
    FaceNode*     CreatePolygon(std::vector<PointNode*>& pointsVector) const;
    FaceNode*     CreateFace(Vec3 origin, Vec3 size, FaceNode::FaceType eType) const;
    PointNode*    CreatePoint(Vec3 origin) const;
    LineNode*     CreateLine(PointNode* startPoint, PointNode* endPoint) const;
    
private:
    ModelTreeManager& mModelTreeManager;
};

}