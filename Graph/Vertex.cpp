

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
    
Vertex::Vertex(glm::vec3 origin)
    :mOrigin(origin)
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
}
    
Vertex* Vertex::CWNeighbourForNeighbour(const Vertex& ref, const Triangle& plane) const
{
    assert(plane.PlaneContains(ref.mOrigin));
    
    std::vector<Vertex*> neigbours;
    Neighbours(neigbours, plane);
    
    
    if (neigbours.size() == 1) {
        return NULL;
    }
    else if (neigbours.size() == 2) {
        if (neigbours[0] == &ref) {
            return neigbours[1];
        } else {
            return neigbours[0];
        }
    }
    
    assert(neigbours.size() > 2);
    
    float minAngle = 400;
    int result = 0;
    for (int i = 0; i < neigbours.size(); ++i) {

        if (neigbours[i] != &ref) {
            float angle = CWAngle(ref, *neigbours[i]);
            if (angle < minAngle) {
                minAngle = angle;
                result = i;
            }
        }
    }
    
    return neigbours[result];
}

float Vertex::CWAngle(const Vertex& A, const Vertex& B) const
{
    glm::vec3 vA = A.mOrigin - mOrigin;
    glm::vec3 vB = B.mOrigin - mOrigin;
    return Vector::CWAngle(glm::normalize(vA), glm::normalize(vB));
}
    

    
}

