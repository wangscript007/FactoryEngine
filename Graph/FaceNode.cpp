
#include <Graph/FaceNode.h>
#include <Graph/LineNode.h>
#include <Graph/PointNode.h>
#include <Geometry/Triangle.h>
#include <Graph/Edge.h>
#include <Processing/ColorPickingMapper.h>
#include <Processing/FaceTraversal.h>


namespace ftr {
    
    
FaceNode::~FaceNode()
{
    
}
    
FaceNode::FaceNode(const std::vector<Vertex*>& vertexes)
    :mVertexes(vertexes)
{
    std::vector<Edge*> edges;
    GetEdges(edges);
    for (Edge *edge : edges) {
        edge->mFaces.push_back(this);
    }
}

FaceNode::FaceNode(const std::vector<glm::vec3>& points)
{
    assert(points.size() > 2);
    
    std::vector<PointNode*> pointNodes;
    for (int i = 0; i < points.size(); ++i) {
        pointNodes.push_back(new PointNode(points[i]));
    }
//    InitWithPointNodes(pointNodes);
}
    
FaceNode::FaceNode(const std::vector<PointNode*>& pointNodes)
{
//    InitWithPointNodes(pointNodes);
}
    
void FaceNode::Render(Layer& layer)
{
    if (mInvalid) {
        if (mSelected) {
            mPolygonPrimitive.mColor = glm::vec4(44/255.0f, 64/255.0f, 0.5f, 127/2555.0f);
        } else {
            mPolygonPrimitive.mColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
        }
        glm::vec3 color = glm::vec3(ColorPickingMapper::ColorFromInt(mPickingId));
        mPolygonPrimitive.mPickingColor = glm::vec4(color.x, color.y, color.z, 1.0f);
        mPolygonPrimitive.Clear();
        for (Vertex *vertex : mVertexes) mPolygonPrimitive.AddPoint(vertex->mOrigin);
        mPolygonPrimitive.setOption(Primitive::kUseDepth, true);
    }
    layer.AddPrimitive(mPolygonPrimitive);
    Node::Render(layer);
}
    
glm::vec3 FaceNode::Center() const
{
    glm::vec3 sum;
    int count = 0;
    for (Vertex *vertex : mVertexes) {
        count++;
        sum += vertex->mOrigin;
    }
    return sum/static_cast<float>(count);
}

    
void FaceNode::Invalidate(bool recursively)
{
//    std::cout << "Invalidate\n";
    if (mInvalid) return;
    
    Node::Invalidate(recursively);
    mPolygonPrimitive.Invalidate();
    
    if (recursively) {
        std::vector<PointNode*>nodes;
        GetPointNodes(nodes);
        for (PointNode *node : nodes) {
            node->Invalidate(recursively);
        }
    }
}
    
void FaceNode::PointNodes(std::vector<Node*>& result) const
{
    for (Vertex *vertex : mVertexes) {
        result.push_back(vertex->pointNode());
    }
}
    
void FaceNode::Transform(const glm::mat4& transform)
{
    for (Vertex *vertex : mVertexes) {
        vertex->pointNode()->Transform(transform);
    }
}
    
glm::vec3 FaceNode::SurfaceNormal() const
{
    assert(mVertexes.size() > 2);
    Triangle triangle(mVertexes[0]->mOrigin, mVertexes[1]->mOrigin, mVertexes[2]->mOrigin);
    return triangle.SurfaceNormal();
    
}
    
void FaceNode::GetEdges(std::vector<Edge*>& edges) const
{
    FaceTraversal::EdgesConnectingVertexes(edges, mVertexes);
}

void FaceNode::GetPointNodes(std::vector<PointNode*>& pointNodes) const
{
    for (Vertex *vertex : mVertexes) {
        pointNodes.push_back(vertex->pointNode());
    }
}
    
std::string FaceNode::Description() const
{
    std::stringstream ss;
    for (Vertex *vertex : mVertexes) {
        ss << vertex->mName << " - ";
    }
    return ss.str();
}

}
