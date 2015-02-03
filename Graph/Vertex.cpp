

#include <Graph/Edge.h>
#include <Graph/Vertex.h>
#include <Geometry/Triangle.h>
#include <Geometry/Vector.h>

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
    
void Vertex::Neighbours(std::vector<Vertex*>& neighbours) const
{
    for (auto &edge : mEdges) {
        neighbours.push_back(edge->OtherEnd(*this));
    }
}
    
    
void Vertex::Neighbours(std::vector<Vertex*>& neighbours, const Triangle& plane) const
{
    for (auto &edge : mEdges) {
        Vertex* otherEnd = edge->OtherEnd(*this);
        if (plane.PlaneContains(otherEnd->mOrigin)) {
            neighbours.push_back(otherEnd);
        }
    }
    
    struct Comparator {
        bool operator () (Vertex* vertexA, Vertex* vertexB) {
            return Vector::IsCWOrder(vertexA->mOrigin, vertexB->mOrigin);
        }
    };

    std::sort(neighbours.begin(), neighbours.end(), Comparator());

}
    
}

