
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
    FaceNode() {}
    FaceNode(const std::vector<Edge*>& edges);
    FaceNode(const std::vector<glm::vec3>& points);
    ~FaceNode();
    
    void Render(Layer& layer);
    static void OrderAscending(Edge& edge1, Edge& edge2);
    void BoundByLoopWithEdge(Edge& outerEdge);
    void AddHoleBoundedByLoopWithEdge(Edge& innerEdge);
    
    std::string Description() const;
    
    bool IsValid() const;
    bool IsValid(const std::vector<Edge*>& edges) const;
    
    std::vector<Edge*> GetEdges() const;
    std::vector<PointNode*> GetPointNodes() const;
    
    Edge* outerEdge() const { return mOuterEdge; };
    
    glm::vec3 SurfaceNormal() const;
    
    
    PointNode* mReferencePoint;
private:
    
    void MarkIncidentFaceInLoopWithEdge(Edge& Edge);
    
    std::vector<Edge*> mInnerEdges;
    Edge* mOuterEdge;
    PolygonPrimitive mPolygonPrimitive;
};

}