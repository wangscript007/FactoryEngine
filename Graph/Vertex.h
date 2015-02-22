
#pragma once

namespace ftr {
    
class Edge;
class PointNode;
class Triangle;

class Vertex
{
public:
    Vertex() {};
    Vertex(glm::vec3 origin);
    Vertex(glm::vec3 origin, PointNode& pointNode);
    virtual ~Vertex() {}
    Edge* ConnectTo(Vertex& target);
    bool IsConnectedTo(const Vertex& target) const;
    Edge* EdgeTo(const Vertex& target) const;
    
    PointNode* pointNode() const { return mPointNode; }
    
    std::vector<Edge*> mEdges;
    glm::vec3 mOrigin;
    
    std::string mName;
    
    
    void Neighbours(std::vector<Vertex*>& neighbours) const;
    void Neighbours(std::vector<Vertex*>& neighbours, const Triangle& plane) const;
    
    Vertex* CWNeighbourForNeighbour(const Vertex& ref, const Triangle& plane) const;
    void CWNeighboursForNeighbour(std::vector<Vertex*>& neighbours, const Vertex& ref, const Triangle& plane) const;
    
    void CWNeighboursForNeighbour(std::vector<Vertex*>& neighbours, const Vertex& ref) const;

    
    size_t Degree() const { return mEdges.size(); }

    static float CWAngle(const Vertex& A, const Vertex& B, const Vertex& ref);
private:
    float CWAngle(const Vertex& A, const Vertex& B) const;
    
    PointNode* mPointNode;
    
};
    
}

