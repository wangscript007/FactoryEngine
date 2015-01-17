

#include <Graph/Edge.h>
#include <Graph/Vertex.h>

namespace ftr {
    
Edge* Vertex::ConnectTo(Vertex& target)
{
    Edge* edge = new Edge(*this, target);
    mEdges.push_back(edge);
    target.mEdges.push_back(edge);
    return edge;
}
    
}

