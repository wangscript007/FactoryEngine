
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
        bool FoundFace() const { return edgesVector.size() > 2; }
        void Clear() { edgesVector.clear(); } 
    };
    
    FaceTraversal(Edge& startEdge);
    virtual ~FaceTraversal();
    
    void Find(Result& result, Result* ignoreResult = NULL);
    
    static bool  IsSameFace(const Result& resultA, const Result& resultB);
    static void  Reverse(Result& result);
    static Edge* AnyUsedEdge(const Result& result);
    
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

