
#include <Graph/Edge.h>
#include <Graph/FaceNode.h>
#include <Graph/Vertex.h>

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
    
std::string Edge::Description() const
{
    std::stringstream ss;
    ss << "(" << mVertexA->mName << (IsFull()? "-#-" : "- -") << mVertexB->mName << ")";
    return ss.str();
}
    
}

