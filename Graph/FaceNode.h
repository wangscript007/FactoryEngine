
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
class Vertex;

class FaceNode : public Node
{
public:
    virtual enum Type        Type() const { return kFace; }
    
    FaceNode() {}
    FaceNode(const std::vector<Vertex*>& vertexes);
    FaceNode(const std::vector<PointNode*>& pointNodes);
    FaceNode(const std::vector<glm::vec3>& points);
    ~FaceNode();
    
    void Render(Layer& layer);
    virtual void Transform(const glm::mat4& transform);
    void Invalidate(bool recursively);
    void PointNodes(std::vector<Node*>& result) const;

    void GetEdges(std::vector<Edge*>& edges) const;
    void GetPointNodes(std::vector<PointNode*>& pointNodes) const;
    
    glm::vec3 Center() const;
    glm::vec3 SurfaceNormal() const;
    
    std::string Description() const;
    
    glm::vec3 IntersectionPoint(const Segment& segment) const;
    
private:
    PolygonPrimitive mPolygonPrimitive;
    std::vector<Vertex*> mVertexes;
};

}