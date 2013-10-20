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
    
    PointNode*    CreatePoint(glm::vec3 origin) const;
    LineNode*     CreateLine(PointNode* startPoint, PointNode* endPoint) const;
    
private:
    ModelTree& mModelTree;
};

}