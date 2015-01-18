

#pragma once

namespace ftr {
    
class Vertex;
class Edge;

class FaceTraversal
{
public:
    struct Result
    {
        bool Found() const { return mVertexes.size() > 2; }
        std::vector<Vertex*>mVertexes;
    };
    
    FaceTraversal(Vertex& vertex);
    void Find(Result& result);
    virtual ~FaceTraversal() {}
    
    
    std::string Description() const;
private:
    bool Find(Vertex& current);
    
    void AppendResult(Vertex& vertex);
    
    bool IsInPlane(const Vertex& vertex);
    bool IsPrev(const Vertex& vertex) const;
    bool IsInResultPath(const Vertex& vertex) const;
    bool IsVisited(const Vertex& vertex) const;
    
    Vertex& mVertex;
    Triangle* mTriangle;
    
    Result* mResult;
};
    
}

