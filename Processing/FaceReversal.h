
#include <Processing/FaceTraversal.h>

namespace ftr {
    
class Edge;
class PointNode;
    
class FaceReversal
{
public:
    FaceReversal();
    
    struct Stats
    {
        int visitedNodes;
        int reversedEdges;
        Stats() : visitedNodes(0), reversedEdges(0) {}
        void Reset() {
            visitedNodes = 0;
            reversedEdges = 0;
        }
    };
    
    struct Conflict
    {
        Edge* edge;
        Edge* edgeBefore;
        Edge* edgeAfter;
        Conflict() : edge(NULL), edgeBefore(NULL), edgeAfter(NULL) {}
    };
    
    static Conflict ConflictInTraversalResult(const FaceTraversal::Result& traversalResult);
    
    void ReverseIslandStartingAtNode(PointNode& startNode);
    void ReverseIslandWithBridgeEdge(Edge& edge);
    void ReverseIslandToResolveConflict(const Conflict& conflict);
    
    Stats stats() const { return mStats; }
    
private:
    void ReverseRecursively(PointNode& pointNode);
    void ResetVisitStates();
    void VisitEdge(Edge& edge);
    void VisitNode(PointNode& node);
    void PrintStats();
    
    static void PrintConflict(const Conflict& conflict);
    
    bool WouldCrossConflictedIslandBorder(const PointNode& pointNode) const;
    
    PointNode* mStartNode;
    PointNode* mStopNode;
    
    Conflict mConflict;
    Stats mStats;
  
    std::vector<Edge*> mVisitedEdges;
    std::vector<PointNode*> mVisitedNodes;
};

}