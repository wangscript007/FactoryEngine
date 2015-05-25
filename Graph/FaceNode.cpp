
#include <Graph/FaceNode.h>
#include <Graph/LineNode.h>
#include <Graph/PointNode.h>
#include <Graph/Edge.h>
#include <Geometry/Triangle.h>
#include <Geometry/Segment.h>
#include <Processing/ColorPickingMapper.h>
#include <Processing/FaceTraversal.h>
#include <Render/Primitive.h>


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
//    std::cout << "Found -----------\n" <<  Description() << "\n\n";
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
        
        { // debug arrows
            FT_DELETE_VECTOR(mLinePrimitives);
            for (int i = 0; i < mVertexes.size() - 1; i++) {
                mLinePrimitives.push_back(ArrowForSegment(Segment(mVertexes[i]->mOrigin, mVertexes[i+1]->mOrigin)));
                layer.AddPrimitive(*mLinePrimitives.back());
            }
            mLinePrimitives.push_back(ArrowForSegment(Segment((*mVertexes.back()).mOrigin, (*mVertexes.begin())->mOrigin)));
            layer.AddPrimitive(*mLinePrimitives.back());
        }
        
        mPolygonPrimitive.setOption(Primitive::kUseDepth, true);
    }
    layer.AddPrimitive(mPolygonPrimitive);
    Node::Render(layer);
}
    
LinePrimitive* FaceNode::ArrowForSegment(const Segment& segment) const
{
    LinePrimitive* primitive = new LinePrimitive();
    segment.Direction();
    glm::vec3 start = segment.Center();
    glm::vec3 end =  glm::normalize(glm::cross(SurfaceNormal(), segment.Direction()));
    end = end - glm::normalize(segment.Direction());
    end *= 0.2;
    primitive->mBegin = start;
    primitive->mEnd = start + end;
    primitive->mColor = glm::vec4(1.0f, 0.2f, 0.3f, 1.0f);
    primitive->setOption(Primitive::kUseDepth, true);
    return primitive;
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
    if (mInvalid) return;
    
    Node::Invalidate(recursively);
    mPolygonPrimitive.Invalidate();
    
    for (LinePrimitive* linePrimitive : mLinePrimitives) {
        linePrimitive->Invalidate();
    }
    
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
    
bool FaceNode::AscendingOrder(const Vertex& begin, const Vertex& end) const
{
    auto it = std::find(mVertexes.begin(), mVertexes.end(), &begin);
    if (it == mVertexes.end()) return false;
    
    if (*it == mVertexes.back()) {
        return &end == mVertexes.front();
    } else {
        return &end == *(it+1);
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
    
glm::vec3 FaceNode::IntersectionPoint(const Segment& segment) const
{
    return mPolygonPrimitive.IntersectionPoint(segment);
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
