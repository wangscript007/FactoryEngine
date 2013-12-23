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
    
FaceNode* FaceTraversal::FindAndCreateFaceContainingNode(PointNode& pointNode)
{
    Edge* itrEdge = pointNode.mEdge;
    if (!itrEdge) return NULL;
    FaceNode* face = NULL;

    do {
        if (itrEdge->originNode() == &pointNode) {
            if (itrEdge->IsFree()) {
                face = FindAndCreateFaceContainingEdge(*itrEdge);
                if (face) break;
            }
        }
        
        if ((itrEdge->originNode() == &pointNode) && itrEdge->prev()) {
            itrEdge = itrEdge->prev();
        } else {
            itrEdge = itrEdge->twin();
        }
    } while (itrEdge != pointNode.mEdge);
    
    return face;
}
    
FaceNode* FaceTraversal::FindAndCreateFaceContainingEdge(Edge& edge)
{
    Edge* itrEdge = &edge;
    FaceNode* face = NULL;
    printf("---------------------------------\n");
    
    int i = 0;
    while (itrEdge->next()
           && itrEdge->next()->IsFree()
           && (itrEdge->next() != &edge)
           && itrEdge->next()->IsCCWCountingFrom(*itrEdge)
           && i < 2)
    {
        printf("%s\n", itrEdge->Description().c_str());
        itrEdge = itrEdge->next();
        i++;
    }
    
    if (&edge == itrEdge->next()) {
        face = new FaceNode();
        face->BoundByLoopWithEdge(edge);
    }
    if (face) {
        printf("New face:%s\n", face->Description().c_str());
    }
    return face;
}
    
    
}

