
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
    
    void Find(Result& result, Result* ignoreResult = NULL);
    
    static bool IsSameFace(const Result& resultA, const Result& resultB);
    static void Reverse(Result& result);
    static bool HasUsedEdges(const Result& result);
    
private:
    bool Find(Edge* startEdge);
    void CreatePlane();
    void PrintEdgesRoute() const;
    
    bool PathContainsNode(const PointNode& pointNode);
    bool IsSamePlane(const ftr::Edge& edge);
    bool IsNotTraversingBackwards(const ftr::Edge& edge) const;
    
    Edge* mStartEdge;
    PointNode* mTargetNode;
    Triangle* mPlane;
    Result* mResult;
    Result* mIgnoreResult;
    
};
    
}

