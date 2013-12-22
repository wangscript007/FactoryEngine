// 
//  Copyright (c) 2012 Dimention. All rights reserved.
//

#include <Model/ModelFactory.h>
#include <Model/FaceTraversal.h>

namespace ftr {

ModelFactory::ModelFactory(ModelTree& ModelTree)
    :mModelTree(ModelTree)
{
    
}

PointNode* ModelFactory::CreatePoint(glm::vec3 origin) const
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
    
FaceNode* ModelFactory::TryToCreateFaceByConnectingNode(PointNode& pointNode) const
{
    return FaceTraversal::TryToCreateFaceByConnectingNode(pointNode);
}
    
}