// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#pragma once

#include <Model/PointNode.h>
#include <Model/FaceNode.h>
#include <Model/LineNode.h>

namespace ftr {

class ModelTree;
//
// 
//
class ModelFactory
{
public:
    ModelFactory(ModelTree& ModelTree);
    ~ModelFactory() {}
    
    FaceNode*     CreateRectangle(const glm::vec3& origin, const glm::vec3& size) const;
    FaceNode*     CreateCircle(glm::vec3 origin, float radius, int iCount) const;
    FaceNode*     CreatePolygon(std::vector<PointNode*>& pointsVector) const;
    FaceNode*     CreateFace(glm::vec3 origin, glm::vec3 size, FaceNode::FaceType eType) const;
    PointNode*    CreatePoint(glm::vec3 origin) const;
    LineNode*     CreateLine(PointNode* startPoint, PointNode* endPoint) const;
    
private:
    ModelTree& mModelTree;
};

}