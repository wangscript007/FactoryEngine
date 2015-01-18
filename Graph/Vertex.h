
#pragma once

namespace ftr {
    
class Edge;

class Vertex
{
public:
    Vertex() {};
    Vertex(glm::vec3 origin);
    virtual ~Vertex() {}
    Edge* ConnectTo(Vertex& target);
    Edge* EdgeTo(Vertex& target);
    
    std::vector<Edge*> mEdges;
    glm::vec3 mOrigin;
    
    std::string mName;
    
    size_t Degree() const { return mEdges.size(); }
private:
    
};
    
}

