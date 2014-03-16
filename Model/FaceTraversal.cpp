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
#include <Model/PointNodeIterator.h>

namespace ftr {
    
FaceTraversal::FaceTraversal(Edge& startEdge)
    : mStartEdge(&startEdge),
    mTargetNode(startEdge.originNode())
{
    
}

void FaceTraversal::Find()
{
    std::cout
    << "Find route from " << mStartEdge->targetNode()->mName
    << " to "<<  mStartEdge->originNode()->mName << std::endl;
    mEdgesVector.clear();
    mEdgesVector.push_back(mStartEdge);
    Find(mStartEdge->twin());
    
    if (mEdgesVector.size() < 3) {
        mEdgesVector.clear();
    } else {
        std::cout << "FOUND: ";
        for(int i = 0; i < mEdgesVector.size(); ++i) {
            std::cout << mEdgesVector[i]->Name() << " ";
        }
        std::cout << std::endl;
    }
}
    
bool FaceTraversal::Find(ftr::Edge *startEdge)
{
    std::cout << "Checking " << startEdge->Name() << std::endl;
    PointNode* originNode = startEdge->originNode();
    for(PointNode::Iterator i = originNode->Begin(); i != originNode->End(); ++i)
    {
        ftr::Edge* iEdge = *i;
        if (iEdge != startEdge->twin() && iEdge->IsFree())
        {
            if (iEdge->targetNode() == mTargetNode)
            {
                mEdgesVector.push_back(iEdge);
                return true;
            }
            else if (iEdge->next()) {
                bool samePlane = true;
                bool isCW = true;
                if (mEdgesVector.size() > 0) {
                    // samePlane check if plane would be same as first two vector elements
                    isCW = iEdge->IsCCWCountingFrom(*mEdgesVector.back());
                }
                if (samePlane && isCW)
                {
                    mEdgesVector.push_back(iEdge);
                    
                    if (Find(iEdge->next()))
                    {
                        return true;
                    }
                    mEdgesVector.pop_back();
                }
            }
        }
    }
    return false;
}
    
}

