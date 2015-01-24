

#include <Graph/Edge.h>
#include <Graph/Vertex.h>

namespace ftr {
    
Vertex::Vertex(glm::vec3 origin, PointNode& pointNode)
    :mOrigin(origin)
    ,mName("-")
    ,mPointNode(&pointNode)
{
    
}
    
bool Vertex::IsConnectedTo(const Vertex& target) const
{
    return EdgeTo(target) != NULL;
}
    
Edge* Vertex::ConnectTo(Vertex& target)
{
    assert(!IsConnectedTo(target));
    Edge* edge = new Edge(*this, target);
    mEdges.push_back(edge);
    target.mEdges.push_back(edge);
    return edge;
}
    
Edge* Vertex::EdgeTo(const Vertex& target) const
{
    for (auto &edge : mEdges) {
        if (edge->OtherEnd(*this) == &target) {
            return edge;
        }
    }
    return NULL;
}
    
}

