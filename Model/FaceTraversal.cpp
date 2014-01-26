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
    
FaceTraversal::FaceTraversal(Edge& startEdge)
    : mStartEdge(&startEdge),
    mTargetNode(startEdge.originNode())
{
    
}

void FaceTraversal::Find()
{
    mEdgesVector.clear();
    mEdgesVector.push_back(mStartEdge);
    Find(mStartEdge->twin());
}
    
bool FaceTraversal::Find(ftr::Edge *startEdge)
{
    PointNode* originNode = mStartEdge->originNode();
    PointNode::Iterator i = originNode->Begin();
    for(; i != originNode->End(); ++i) {
        ftr::Edge* iEdge = *i;
        if (iEdge->originNode() == originNode) {
            if (iEdge != startEdge->twin() && iEdge->IsFree()) {
                if (iEdge->twin()->originNode() == mTargetNode) {
                    return true;
                } else {
                    if (iEdge->next()) {
                        bool samePlane = true;
                        if (mEdgesVector.size() > 1) {
                            // samePlane check if plane would be same as first two vector elements
                        }
                        if (samePlane) {
                            mEdgesVector.push_back(iEdge);
                            if (Find(iEdge->next())) {
                                return true;
                            }
                            mEdgesVector.pop_back();
                        }
                    }
                    
                }
            }
        }
    }
    return false;
}
    
}

