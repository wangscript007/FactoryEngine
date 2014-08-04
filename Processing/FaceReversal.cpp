
#include <Processing/FaceReversal.h>
#include <Graph/Edge.h>
#include <Graph/PointNode.h>

namespace ftr {

FaceReversal::Conflict FaceReversal::ConflictInTraversalResult(const FaceTraversal::Result& traversalResult)
{
    Conflict conflict;
    const std::vector<Edge*> &edgesVector = traversalResult.edgesVector;
    
    assert(traversalResult.hasUsedEdges);
    int conflictsCount = 0;
    int conflictIndex = 0;
    for (int i = 0; i < edgesVector.size(); ++i) {
        Edge* edge = edgesVector[i];
        if (!edge->IsFree()) {
            conflict.edge = edge;
            conflictIndex = i;
            conflictsCount++;
        }
    }
    
    assert(conflictsCount == 1);
    assert(conflict.edge);
    assert(!conflict.edge->IsFree());
    assert(conflict.edge->twin()->IsFree());
    
    if (conflictIndex == 0) {
        conflict.edgeBefore = edgesVector.back();
        conflict.edgeAfter = edgesVector[1];
    }
    else if (conflictIndex == edgesVector.size())
    {
        conflict.edgeBefore = edgesVector[conflictIndex-1];
        conflict.edgeAfter = edgesVector.front();
    }
    else {
        conflict.edgeBefore = edgesVector[conflictIndex-1];
        conflict.edgeAfter = edgesVector[conflictIndex+1];
    }
    assert(conflict.edgeBefore);
    assert(conflict.edgeAfter);
    
    PrintConflict(conflict);
    
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
    mStats.Reset();
    
    mConflict = conflict;
    ReverseRecursively(*mConflict.edge->originNode());
    
    PrintStats();
    ResetVisitStates();
}
    
void FaceReversal::ReverseRecursively(PointNode& pointNode)
{
    bool reachedStopNode = pointNode.mVisited || &pointNode == mStopNode;
    if (reachedStopNode || WouldCrossConflictedIslandBorder(pointNode)) {
        return;
    }
    
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
    
bool FaceReversal::WouldCrossConflictedIslandBorder(const PointNode& pointNode) const
{
    if (mConflict.edge) {
        if (&pointNode == mConflict.edgeAfter->targetNode() ||
            &pointNode == mConflict.edgeBefore->originNode())
        {
            return true;
        }
    }
    return false;
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
    
void FaceReversal::PrintConflict(const Conflict& conflict)
{
    std::cout << std::endl;
    std::cout << "CONFLICT EDGE: " << conflict.edge->Description() << std::endl;
    std::cout << "Edge before: " << conflict.edgeBefore->Description() << std::endl;
    std::cout << "Edge after: " << conflict.edgeAfter->Description() << std::endl;
    std::cout << std::endl;
}

}