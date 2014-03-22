
#pragma once

namespace ftr {
    
class FaceNode;
class PointNode;
class Edge;
class Plane;

class FaceTraversal
{
public:
    struct Result
    {
        bool hasUsedEdges;
        std::vector<Edge*> edgesVector;
    };
    
    FaceTraversal(Edge& startEdge);
    virtual ~FaceTraversal() {}
    
    void Find(Result& result);
    
    static bool IsSameFace(const Result& resultA, const Result& resultB);
    
private:
    bool Find(Edge* startEdge);
    void CreatePlane();
    void PrintEdgesRoute() const;
    
    Edge* mStartEdge;
    PointNode* mTargetNode;
    Plane* mPlane;
    Result* mResult;
    
};
    
}

