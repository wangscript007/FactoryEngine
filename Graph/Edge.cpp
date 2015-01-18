
#include <Graph/Edge.h>
#include <Graph/FaceNode.h>
#include <Graph/Vertex.h>

namespace ftr {
    
Edge::Edge(Vertex& vertexA, Vertex& vertexB)
    :mVertexA(&vertexA),
    mVertexB(&vertexB)
{
    
}
    
Vertex* Edge::OtherEnd(Vertex& vertex)
{
    if (mVertexA == &vertex) {
        assert(mVertexB != &vertex);
        return mVertexB;
    } else {
        assert(mVertexB == &vertex);
        assert(mVertexA != &vertex);
        return mVertexA;
    }
}
    
}

