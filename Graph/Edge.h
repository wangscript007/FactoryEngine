
#pragma once

namespace ftr {
    
class Vertex;
class FaceNode;

class Edge
{
public:
    Edge(Vertex& vertexA, Vertex& vertexB);
    virtual ~Edge() {}
    
    Vertex* OtherEnd(Vertex& vertex);
    
    std::vector<FaceNode*>mFaces;
private:
    
    Vertex* mVertexA;
    Vertex* mVertexB;
};
    
}

