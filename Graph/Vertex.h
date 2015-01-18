
#pragma once

namespace ftr {
    
class Edge;
class PointNode;

class Vertex
{
public:
    Vertex() {};
    Vertex(glm::vec3 origin, PointNode& pointNode);
    virtual ~Vertex() {}
    Edge* ConnectTo(Vertex& target);
    Edge* EdgeTo(Vertex& target);
    
    PointNode* pointNode() const { return mPointNode; }
    
    std::vector<Edge*> mEdges;
    glm::vec3 mOrigin;
    
    std::string mName;
    
    
    size_t Degree() const { return mEdges.size(); }
private:
    
    PointNode* mPointNode;
    
};
    
}

