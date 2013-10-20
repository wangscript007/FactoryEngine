
//
// Node: FaceNode should consits of concave polygons array
//
#pragma once

#include <Model/Node.h>

namespace ftr {

class Polygon;
class LineNode;
class PointNode;

class FaceNode : public Node
{
public:
    
    FaceNode();
    ~FaceNode();
    
    void Render(Layer& layer);
    
private:
    
};

}