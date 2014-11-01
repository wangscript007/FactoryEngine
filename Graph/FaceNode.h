
//
// Node: FaceNode should consits of concave polygons array
//
#pragma once

#include <Graph/Node.h>

namespace ftr {

class Polygon;
class LineNode;
class PointNode;
class Edge;

class FaceNode : public Node
{
public:
    virtual enum Type        Type() const { return kFace; }
    
    FaceNode() {}
    FaceNode(const std::vector<Edge*>& edges);
    FaceNode(const std::vector<glm::vec3>& points);
    ~FaceNode();
    
    void Render(Layer& layer);
    virtual void Transform(const glm::mat4& transform);
    void Invalidate(bool recursively);
    
    static void OrderAscending(Edge& edge1, Edge& edge2);
    void BoundByLoopWithEdge(Edge& outerEdge);
    void AddHoleBoundedByLoopWithEdge(Edge& innerEdge);
    
    std::string Description() const;
    
    bool IsValid() const;
    bool IsValid(const std::vector<Edge*>& edges) const;
    
    std::vector<Edge*> GetEdges() const;
    std::vector<PointNode*> GetPointNodes() const;
    glm::vec3 Center() const;
    
    
    Edge* outerEdge() const { return mOuterEdge; };
    void setOuterEdge(Edge* outerEdge) { mOuterEdge = outerEdge; };
    
    glm::vec3 SurfaceNormal() const;
    
    
    PointNode* mReferencePoint;
private:
    void InitWithEdges(const std::vector<Edge*>& edges);
    void MarkIncidentFaceInLoopWithEdge(Edge& Edge);
    
    std::vector<Edge*> mInnerEdges;
    Edge* mOuterEdge;
    PolygonPrimitive mPolygonPrimitive;
};

}