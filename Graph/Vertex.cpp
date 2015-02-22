

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
    
    std::vector<Vertex*> neighbours;
    CWNeighboursForNeighbour(neighbours, ref, plane);
    
    if (neighbours.size() == 0) {
        return NULL;
    }
    return neighbours[0];
}
    
void Vertex::CWNeighboursForNeighbour(std::vector<Vertex*>& neighbours, const Vertex& ref, const Triangle& plane) const
{
 
    Neighbours(neighbours, plane);
    
    struct Comparator {
        Comparator(const Vertex& reference, const Vertex& current)
        : mReference(reference), mCurrent(current) {}
        Vertex mReference;
        Vertex mCurrent;
        
        bool operator () (Vertex* vertexA, Vertex* vertexB) {
            float angleA = CWAngle(mReference, *vertexA, mCurrent);
            float angleB = CWAngle(mReference, *vertexB, mCurrent);
            return angleA < angleB;
        }
    };
    
    std::sort(neighbours.begin(), neighbours.end(), Comparator(ref, *this));
    if (neighbours.size() > 1) {
        neighbours.erase(neighbours.end()-1);
    }
}
    
void Vertex::CWNeighboursForNeighbour(std::vector<Vertex*>& neighbours, const Vertex& ref) const
{
    
    Neighbours(neighbours);
    
    struct Comparator {
        Comparator(const Vertex& reference, const Vertex& current)
        : mReference(reference), mCurrent(current) {}
        Vertex mReference;
        Vertex mCurrent;
        
        bool operator () (Vertex* vertexA, Vertex* vertexB) {
            float angleA = CWAngle(mReference, *vertexA, mCurrent);
            float angleB = CWAngle(mReference, *vertexB, mCurrent);
            return angleA < angleB;
        }
    };
    
    std::sort(neighbours.begin(), neighbours.end(), Comparator(ref, *this));
    if (neighbours.size() > 1) {
        neighbours.erase(neighbours.end()-1);
    }
}


float Vertex::CWAngle(const Vertex& A, const Vertex& B, const Vertex& ref)
{
    glm::vec3 vA = A.mOrigin - ref.mOrigin;
    glm::vec3 vB = B.mOrigin - ref.mOrigin;
    return Vector::CWAngle(glm::normalize(vA), glm::normalize(vB));

}


float Vertex::CWAngle(const Vertex& A, const Vertex& B) const
{
    return CWAngle(A, B, *this);
}
    

    
}

