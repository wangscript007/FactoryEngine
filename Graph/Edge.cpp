
#include <Graph/Edge.h>
#include <Graph/FaceNode.h>
#include <Graph/Vertex.h>
#include <Geometry/Vector.h>

namespace ftr {
    
Edge::Edge(Vertex& vertexA, Vertex& vertexB)
    :mVertexA(&vertexA),
    mVertexB(&vertexB)
{
    
}
    
Vertex* Edge::OtherEnd(const Vertex& vertex) const
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
        
size_t Edge::Degree() const
{
    return std::max(mVertexA->Degree(), mVertexB->Degree());
}
    
bool Edge::IsFull() const
{
    assert(Degree() > mFaces.size());
    return (Degree() - 1 == mFaces.size());
}
    
bool Edge::ContainsFace(const FaceNode& face) const
{
    auto it = std::find(mFaces.begin(), mFaces.end(), &face);
    
    return it != mFaces.end();
}
    
FaceNode* Edge::Face(const Vertex& begin, const Vertex& end, const Triangle& plane)
{
    glm::vec3 surfaceNormal = plane.SurfaceNormal();
    for (FaceNode* face : mFaces) {
        if (face->AscendingOrder(begin, end)) {
            if (Vector::IsParallel(surfaceNormal, face->SurfaceNormal())) {
                return face;
            }
        }
    }
    return NULL;
}
    
std::string Edge::Description() const
{
    std::stringstream ss;
    ss << "(" << mVertexA->mName << "-" << mVertexB->mName << ")";
    return ss.str();
}
    
}

