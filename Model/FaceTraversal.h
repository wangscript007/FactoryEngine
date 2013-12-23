
#pragma once

namespace ftr {
    
class FaceNode;
class PointNode;
class Edge;

class FaceTraversal
{
public:
    static FaceNode* FindAndCreateFaceContainingNode(PointNode& pointNode);
    static FaceNode* FindAndCreateFaceContainingEdge(Edge& edge);
    
private:
};
    
}

