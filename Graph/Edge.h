
#pragma once

namespace ftr {
    
class Vertex;
class FaceNode;
class LineNode;

class Edge
{
public:
    Edge(Vertex& vertexA, Vertex& vertexB);
    virtual ~Edge() {}
    
    Vertex* OtherEnd(const Vertex& vertex) const;
    
    std::vector<FaceNode*> mFaces;
    
    bool IsFull() const;
    size_t Degree() const;
    bool ContainsFace(const FaceNode& face) const;
    
    FaceNode* Face(const Vertex& begin, const Vertex& end, const Triangle& plane);
    
    LineNode* mLineNode;
    
    std::string Description() const;
    
    
    
    
    
private:
    
    Vertex* mVertexA;
    Vertex* mVertexB;
};
    
}

