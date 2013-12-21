
//
// Node: FaceNode should consits of concave polygons array
//
#pragma once

#include <Model/Node.h>

namespace ftr {

class Polygon;
class LineNode;
class PointNode;
class Edge;

class FaceNode : public Node
{
public:
    FaceNode();
    ~FaceNode();
    
    void Render(Layer& layer);
    
    void BoundByLoopWithEdge(Edge& outerEdge);
    void AddHoleBoundedByLoopWithEdge(Edge& innerEdge);
    
    std::string Description() const;
private:
    void MarkIncidentFaceInLoopWithEdge(Edge& Edge);
    std::vector<Edge*> mInnerEdges;
    Edge* mOuterEdge;
};

}