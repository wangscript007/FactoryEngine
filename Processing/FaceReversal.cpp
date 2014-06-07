
#include <Processing/FaceReversal.h>
#include <Graph/Edge.h>
#include <Graph/PointNode.h>

namespace ftr {

FaceReversal::Conflict FaceReversal::ConflictInTraversalResult(const FaceTraversal::Result& traversalResult)
{
    Conflict conflict;
    assert(traversalResult.hasUsedEdges);
    int count = 0;
    int index = 0;
    for (auto &edge : traversalResult.edgesVector) {
        if (!edge->IsFree()) {
            conflict.usedEdge = edge;
            count++;
        } else {
            index++;
        }
        
    }
    assert(count == 1);
    assert(conflict.usedEdge);
    
    if (index == 0) {
        conflict.incomingEdge = traversalResult.edgesVector.back();
        conflict.outgoingEdge = traversalResult.edgesVector[1];
    } else if (index == traversalResult.edgesVector.size()) {
        conflict.incomingEdge = traversalResult.edgesVector[index-1];
        conflict.outgoingEdge = traversalResult.edgesVector.front();
    } else {
        conflict.incomingEdge = traversalResult.edgesVector[index-1];
        conflict.outgoingEdge = traversalResult.edgesVector[index+1];
    }
    assert(conflict.incomingEdge);
    assert(conflict.outgoingEdge);
    
    return conflict;
}
    
FaceReversal::FaceReversal()
    :   mStopNode(NULL),
        mStartNode(NULL)
{}

void FaceReversal::ReverseIslandStartingAtNode(PointNode& pointNode)
{
    mStats.Reset();
    
    mStartNode = &pointNode;
    ReverseRecursively(*mStartNode);
    
    PrintStats();
    ResetVisitStates();
}

void FaceReversal::ReverseIslandWithBridgeEdge(Edge& edge)
{
    mStopNode = edge.targetNode();
    ReverseIslandStartingAtNode(*edge.originNode());
}
    
void FaceReversal::ReverseIslandToResolveConflict(const Conflict& conflict)
{
    
}
    
void FaceReversal::ReverseRecursively(PointNode& pointNode)
{
    if (pointNode.mVisited || &pointNode == mStopNode) return;
    
    VisitNode(pointNode);
    
    for(PointNode::Iterator i = pointNode.Begin(); i != pointNode.End(); ++i)
    {
        ftr::Edge* edge = *i;
        if (!edge->mVisited) {
            edge->ReverseFaceProperties();
            VisitEdge(*edge);
            ReverseRecursively(*edge->targetNode());
        }
    }
}
    
void FaceReversal::VisitNode(PointNode& pointNode)
{
    mVisitedNodes.push_back(&pointNode);
    mStats.visitedNodes++;
    pointNode.mVisited = true;
}
    
void FaceReversal::VisitEdge(Edge& edge)
{
    mVisitedEdges.push_back(&edge);
    mStats.reversedEdges++;
    edge.mVisited = true;
    edge.twin()->mVisited = true;
}

    
    
void FaceReversal::ResetVisitStates()
{
    for (auto &pointNode : mVisitedNodes) {
        pointNode->mVisited = false;
    }
    mVisitedNodes.clear();

    for (auto &edge : mVisitedEdges) {
        edge->mVisited = false;
        edge->twin()->mVisited = false;
    }
    mVisitedEdges.clear();
}
    
void FaceReversal::PrintStats()
{
    std::cout << std::endl;
    std::cout << "FACES REVERSED: " << std::endl;
    std::cout << "Visited nodes: " << mStats.visitedNodes << std::endl;
    std::cout << "Reversed edges: " << mStats.reversedEdges << std::endl;
    std::cout << std::endl;
}

}