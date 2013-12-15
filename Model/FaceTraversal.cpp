//
//  FaceTraversal.cpp
//  FactoryEngine
//
//  Created by Edvinas on 10/20/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//



#include <Model/FaceTraversal.h>
#include <Model/PointNode.h>
#include <Model/HalfEdge.h>
#include <Model/FaceNode.h>

namespace ftr {
    
FaceNode* FaceTraversal::CreateFaceByConnectingNode(PointNode& pointNode) const
{
    if (!pointNode.mHalfEdge->HasFreeNextEdge()) {
        return NULL;
    }
    HalfEdge* initialEdge = pointNode.mHalfEdge;
    HalfEdge* currentEdge = pointNode.mHalfEdge;
    FaceNode* face = NULL;
    
    while (currentEdge->HasFreeNextEdge() && (currentEdge->next() != initialEdge)) {
        currentEdge = currentEdge->next();
    }
    if (initialEdge == currentEdge->next()) {
        face = new FaceNode();
        face->BoundByLoopWithHalfEdge(*initialEdge);
    }
    if (face) {
        printf("%s \n%s\n\n", pointNode.mName.c_str(), face->Description().c_str());
    }
    return face;
}
    
    
}

