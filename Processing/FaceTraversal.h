

#pragma once

namespace ftr {
    
class Vertex;
class Edge;
class Triangle;
class FaceNode;

class FaceTraversal
{
public:
    struct Result
    {
        bool Found() const { return mEdges.size() > 2; }
        std::vector<Edge*> mEdges;
        std::vector<Vertex*> mVertexes;
    };

    
    static void EdgesConnectingVertexes(std::vector<Edge*>& edges,
                                        const std::vector<Vertex*>& vertexes);
    
    
    FaceTraversal(Vertex& vertex);
    void Find(Result& result);
    virtual ~FaceTraversal() {}
    
    std::string Description() const;
    std::string Description(Result* result) const;
    
private:
    bool Find(Vertex& current);
    
    void AppendResult(Vertex& vertex);
    
    bool ContainsFace() const;
    bool IsInPlane(const Vertex& vertex);
    Vertex* Prev() const;
    bool IsInResultPath(const Vertex& vertex) const;
    void UpdatePlane();
    
    Vertex& mVertex;
    std::vector<Vertex*>mVertexes;
    Triangle* mPlane;
    
    Result* mResult;
};
    
}

