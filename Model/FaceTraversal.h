
#pragma once

namespace ftr {
    
class FaceNode;
class PointNode;
class Edge;
class Plane;

class FaceTraversal
{
public:
    FaceTraversal(Edge& startEdge);
    virtual ~FaceTraversal() {}
    
    void Find();
    
    std::vector<Edge*>& FaceEdges() { return mEdgesVector; }
    
private:
    bool Find(Edge* startEdge);
    void CreatePlane();
    
    Edge* mStartEdge;
    PointNode* mTargetNode;
    Plane* mPlane;
    std::vector<Edge*> mEdgesVector;
};
    
}

