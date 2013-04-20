
#pragma once

#include <Model/Node.h>
#include <Model/PointNode.h>

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

