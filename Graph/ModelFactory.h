// 
//  Copyright (c) 2012 Dimension. All rights reserved.
//

#pragma once

#include <Graph/PointNode.h>
#include <Graph/LineNode.h>
#include <Graph/FaceNode.h>
#include <Graph/GroupNode.h>
#include <Graph/BodyNode.h>



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