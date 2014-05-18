
#pragma once

namespace ftr {
    
class FaceNode;
class PointNode;
class Edge;
class Triangle;

class FaceTraversal
{
public:
    struct Result
    {
        bool hasUsedEdges;
        std::vector<Edge*> edgesVector;
    };
    
    FaceTraversal(Edge& startEdge);
    virtual ~FaceTraversal();
    
    void Find(Result& result);
    
    static bool IsSameFace(const Result& resultA, const Result& resultB);
    
private:
    bool Find(Edge* startEdge);
    void CreatePlane();
    void PrintEdgesRoute() const;
    
    static bool PathContainsNode(const std::vector<Edge*>& edges, const PointNode& pointNode);
    
    Edge* mStartEdge;
    PointNode* mTargetNode;
    Triangle* mPlane;
    Result* mResult;
    
};
    
}

