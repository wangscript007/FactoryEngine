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
    static int index = 0;
    PointNode* pPoint = new PointNode();
    pPoint->mOrigin = origin;
    index++;
    std::ostringstream convert;
    convert << index;
    pPoint->mName = convert.str();
    return pPoint;
}

LineNode* ModelFactory::CreateLine(PointNode* startPoint, PointNode* endPoint) const
{
    LineNode* line = new LineNode(startPoint, endPoint);
    return line;
}
    
FaceNode* ModelFactory::FindAndCreateFaceContainingNode(PointNode& pointNode) const
{
 //   return FaceTraversal::FindAndCreateFaceContainingNode(pointNode);
}
    
}