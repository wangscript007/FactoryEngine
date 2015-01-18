

#include <Graph/Edge.h>
#include <Graph/Vertex.h>

namespace ftr {
    
Vertex::Vertex(glm::vec3 origin)
    :mOrigin(origin)
    ,mName("-")
{
    
}
    
Edge* Vertex::ConnectTo(Vertex& target)
{
    Edge* edge = new Edge(*this, target);
    mEdges.push_back(edge);
    target.mEdges.push_back(edge);
    return edge;
}
    
}

