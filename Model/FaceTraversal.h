
#pragma once

namespace ftr {
    
class FaceNode;
class PointNode;
class Edge;

class FaceTraversal
{
public:
    FaceTraversal(Edge& startEdge);
    virtual ~FaceTraversal() {}
    
    void Find();
    
    std::vector<Edge*>& FaceEdges() { return mEdgesVector; }
    
private:
    bool Find(Edge* startEdge);
    
    Edge* mStartEdge;
    PointNode* mTargetNode;
    std::vector<Edge*> mEdgesVector;
};
    
}

