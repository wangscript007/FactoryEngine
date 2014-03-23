//
//  FaceTraversal.cpp
//  FactoryEngine
//
//  Created by Edvinas on 10/20/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//


#include <Math/Plane.h>
#include <Model/FaceTraversal.h>
#include <Model/PointNode.h>
#include <Model/Edge.h>
#include <Model/FaceNode.h>
#include <Model/PointNodeIterator.h>

namespace ftr {
    
bool FaceTraversal::IsSameFace(const Result& resultA, const Result& resultB)
{
    bool result = false;
    if (resultA.edgesVector[1] == resultB.edgesVector[resultB.edgesVector.size() - 1]->twin()) {
        result = true;
    }
    return result;
}
    
    
FaceTraversal::FaceTraversal(Edge& startEdge)
    : mStartEdge(&startEdge),
    mPlane(NULL),
    mTargetNode(startEdge.originNode())
{
    
}

void FaceTraversal::Find(Result& result)
{
    mResult = &result;
    std::vector<Edge*>& edgesVector = mResult->edgesVector;
    if (mPlane) {
        FT_DELETE(mPlane);
    }
    
    std::cout
    << "----------------------------------" << std::endl
    << "Find route from " << mStartEdge->targetNode()->mName
    << " to "<<  mStartEdge->originNode()->mName << std::endl;
    edgesVector.clear();
    edgesVector.push_back(mStartEdge);
    
    Find(mStartEdge->twin());
    
    mResult->hasUsedEdges = false;
    if (edgesVector.size() < 3) {
        edgesVector.clear();
    } else {
        
        for(int i = 0; i < edgesVector.size(); ++i) {
            Edge* edge = edgesVector[i];
            if (!edge->IsFree()) {
                mResult->hasUsedEdges = true;
                break;
            }
            
        }
        
        std::cout << "FOUND: ";
        for(int i = 0; i < edgesVector.size(); ++i) {
            std::cout << edgesVector[i]->Name() << " ";
        }
        std::cout << std::endl;
    }
}
    
bool FaceTraversal::Find(ftr::Edge *startEdge)
{
    std::vector<Edge*>& edgesVector = mResult->edgesVector;
    assert(edgesVector.size() >= 1); // must contain initial edge
    
    std::cout << "Checking " << startEdge->Name() << " size: " << edgesVector.size() << std::endl;
    PointNode* originNode = startEdge->originNode();
    
    assert(edgesVector.size() < 20); // too far for simple tests
    
    for(PointNode::Iterator i = originNode->Begin(); i != originNode->End(); ++i)
    {
        ftr::Edge* iEdge = *i;
        if (iEdge != edgesVector.back()->twin())
        {
            if (iEdge->targetNode() == mTargetNode)
            {
                edgesVector.push_back(iEdge);
                return true;
            }
            else if (iEdge->next()) {
                bool samePlane = true;
                bool isCW = true;
                if (edgesVector.size() > 0) {
                    //isCW = iEdge->IsCCWCountingFrom(*edgesVector.back());
                    if (edgesVector.size() > 1) {
                        CreatePlane();
                    } else {
                        FT_DELETE(mPlane);
                    }
                    if (mPlane) {
                        samePlane = mPlane->Contains(iEdge->target());
                    }
                }
                assert(samePlane);
                if (samePlane && isCW)
                {
                    edgesVector.push_back(iEdge);
                    
                    std::cout << "Route: "; PrintEdgesRoute();
                    
                    if (Find(iEdge->next()))
                    {
                        return true;
                    }
                    edgesVector.pop_back();
                }
            }
        }
    }
    //std::cout << "Failed route: "; PrintEdgesRoute();
    return false;
}
    
void FaceTraversal::PrintEdgesRoute() const
{
    for (auto it = mResult->edgesVector.begin(); it != mResult->edgesVector.end(); ++it) {
        std::cout << (*it)->Name() << " - ";
    }
    std::cout << std::endl;
}
    
void FaceTraversal::CreatePlane()
{
    if (!mPlane) {
        std::vector<Edge*>& edgesVector = mResult->edgesVector;
        assert(edgesVector.size() > 1);
        Edge* e1 = edgesVector[0];
        Edge* e2 = edgesVector[1];
        mPlane = new Plane(e1->origin(), e1->target(), e2->target());
    }
}
    
}

