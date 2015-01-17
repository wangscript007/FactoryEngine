
//
// Node: FaceNode should consits of concave polygons array
//
#pragma once

#include <Graph/Node.h>

namespace ftr {

class Polygon;
class LineNode;
class PointNode;

class FaceNode : public Node
{
public:
    virtual enum Type        Type() const { return kFace; }
    
    FaceNode() {}
    FaceNode(const std::vector<PointNode*>& pointNodes);
    FaceNode(const std::vector<glm::vec3>& points);
    ~FaceNode();
    
    void Render(Layer& layer);
    virtual void Transform(const glm::mat4& transform);
    void Invalidate(bool recursively);
    void PointNodes(std::vector<Node*>& result) const;
    
    std::string Description() const;
    
//    std::vector<Edge*> GetEdges() const;
    std::vector<PointNode*> GetPointNodes() const;
    glm::vec3 Center() const;
    
    glm::vec3 SurfaceNormal() const;
    
    
    PointNode* mReferencePoint;
    
private:
    PolygonPrimitive mPolygonPrimitive;
};

}