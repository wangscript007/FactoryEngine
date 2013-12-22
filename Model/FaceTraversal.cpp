//
//  FaceTraversal.cpp
//  FactoryEngine
//
//  Created by Edvinas on 10/20/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//



#include <Model/FaceTraversal.h>
#include <Model/PointNode.h>
#include <Model/Edge.h>
#include <Model/FaceNode.h>

namespace ftr {
    
FaceNode* FaceTraversal::TryToCreateFaceByConnectingNode(PointNode& pointNode)
{
    if (!(pointNode.mEdge && pointNode.mEdge->HasFreeNextEdge())) {
        return NULL;
    }
    Edge* initialEdge = pointNode.mEdge;
    Edge* currentEdge = pointNode.mEdge;
    FaceNode* face = NULL;
    printf("---------------------------------\n");
    while (currentEdge->HasFreeNextEdge() && (currentEdge->next() != initialEdge)) {
        printf("%s\n", currentEdge->Description().c_str());
        currentEdge = currentEdge->next();
        
    }
    if (initialEdge == currentEdge->next()) {
        face = new FaceNode();
        face->BoundByLoopWithEdge(*initialEdge);
    }
    if (face) {
        printf("New face %s \n%s\n\n", pointNode.mName.c_str(), face->Description().c_str());
    }
    return face;
}
    
    
}

