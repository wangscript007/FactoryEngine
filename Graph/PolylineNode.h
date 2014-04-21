
#pragma once

#include <Graph/Node.h>
#include <Graph/PointNode.h>

namespace ftr {

class PolylineNode : Node
{
public:
    typedef std::vector<PointNode*>  TPoinsVector;
    virtual ~PolylineNode() {}
    
private:
    TPoinsVector mPointsVector;
};
    
}

