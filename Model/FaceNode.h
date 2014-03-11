
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
    FaceNode(std::vector<Edge*>& edges);
    ~FaceNode();
    
    void Render(Layer& layer);
    static void OrderAscending(Edge& edge1, Edge& edge2);
    void BoundByLoopWithEdge(Edge& outerEdge);
    void AddHoleBoundedByLoopWithEdge(Edge& innerEdge);
    
    std::string Description() const;
    
private:
    bool IsValid(std::vector<Edge*>& edges) const;
    void MarkIncidentFaceInLoopWithEdge(Edge& Edge);
    
    std::vector<Edge*> mInnerEdges;
    Edge* mOuterEdge;
    PolygonPrimitive mPolygonPrimitive;
};

}