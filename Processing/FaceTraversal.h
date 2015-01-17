

#pragma once

namespace ftr {
    
class Vertex;
class Edge;

class FaceTraversal
{
public:
    struct Result
    {
        
    };
    
    FaceTraversal(Vertex* vertex);
    void Find(Result& result);
    virtual ~FaceTraversal() {}
    
private:
    bool Find(Vertex& vertex);
    
};
    
}

