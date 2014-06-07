
#include <Processing/FaceReversal.h>
#include <Graph/Edge.h>
#include <Graph/PointNode.h>

namespace ftr {
    
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