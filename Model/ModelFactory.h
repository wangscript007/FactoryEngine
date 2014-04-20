// 
//  Copyright (c) 2012 Dimension. All rights reserved.
//

#pragma once

#include <Model/PointNode.h>
#include <Model/LineNode.h>
#include <Model/FaceNode.h>
#include <Model/GroupNode.h>
#include <Model/BodyNode.h>



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
    
    PointNode* CreatePoint(glm::vec3 origin) const;
    LineNode* CreateLine(PointNode* startPoint, PointNode* endPoint) const;
    BodyNode* CreateBody();
    GroupNode* CreateGroup();

    
private:
    ModelTree& mModelTree;
};

}