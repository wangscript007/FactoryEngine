
//
// Node: FaceNode should consits of concave polygons array
//
#pragma once

#include <Model/Node.h>

namespace ftr {

class Polygon;
class LineNode;
class PointNode;
class HalfEdge;

class FaceNode : public Node
{
public:
    FaceNode();
    ~FaceNode();
    
    void Render(Layer& layer);
    
    void BoundByLoopWithHalfEdge(HalfEdge& outerEdge);
    void AddHoleBoundedByLoopWithHalfEdge(HalfEdge& innerEdge);
    
    std::string Description() const;
private:
    void MarkIncidentFaceInLoopWithHalfEdge(HalfEdge& halfEdge);
    std::vector<HalfEdge*> mInnerEdges;
    HalfEdge* mOuterEdge;
};

}