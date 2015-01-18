
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
    
    std::vector<FaceNode*> mFaces;
    
    bool IsFull() const;
    size_t Degree() const;
    
    std::string Description() const;
private:
    
    Vertex* mVertexA;
    Vertex* mVertexB;
};
    
}

