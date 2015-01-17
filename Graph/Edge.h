
#pragma once

namespace ftr {
    
class Vertex;

class Edge
{
public:
    Edge(Vertex& vertexA, Vertex& vertexB);
    virtual ~Edge() {}
    
private:
    Vertex* mVertexA;
    Vertex* mVertexB;
};
    
}

