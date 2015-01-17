
#pragma once

namespace ftr {
    
class Edge;

class Vertex
{
public:
    virtual ~Vertex() {}    
    Edge* ConnectTo(Vertex& target);
    
private:
    std::vector<Edge*> mEdges;
};
    
}

