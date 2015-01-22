// 
//  Copyright (c) 2012 Dimension. All rights reserved.
//

#pragma once

namespace ftr {

class ModelTree;
class PointNode;
class LineNode;
class FaceNode;
class BodyNode;
class GroupNode;
class Vertex;
    
class ModelFactory
{
public:
    ModelFactory(ModelTree& ModelTree);
    ~ModelFactory() {}
    
    PointNode* CreatePoint(glm::vec3 origin) const;
    LineNode* CreateLine(PointNode* startPoint, PointNode* endPoint) const;
    FaceNode* CreateFace(std::vector<PointNode*> pointNodes) const;
    FaceNode* CreateFace(const std::vector<Vertex*>& vertexes);
    BodyNode* CreateBody();
    GroupNode* CreateGroup();

    
private:
    ModelTree& mModelTree;
};

}