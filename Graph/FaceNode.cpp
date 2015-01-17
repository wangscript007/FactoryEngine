
#include <Graph/FaceNode.h>
#include <Graph/LineNode.h>
#include <Graph/PointNode.h>
#include <Geometry/Triangle.h>
#include <Processing/ColorPickingMapper.h>


namespace ftr {
    
    
FaceNode::~FaceNode()
{
    
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
//        Edge* currentEdge = mOuterEdge;
        mPolygonPrimitive.Clear();
//        do {
//            mPolygonPrimitive.AddPoint(currentEdge->origin());
//            if (!currentEdge->next()) {
//                assert(false); // face is messed up!
//            }
//            currentEdge = currentEdge->next();
//        } while (currentEdge != mOuterEdge);
        mPolygonPrimitive.setOption(Primitive::kUseDepth, true);
    }
    layer.AddPrimitive(mPolygonPrimitive);
    Node::Render(layer);
}
    
glm::vec3 FaceNode::Center() const
{
    glm::vec3 sum;
    int count = 0;
//    Edge* currentEdge = mOuterEdge;
//    do {
//        count++;
//        sum += currentEdge->originNode()->mOrigin;
//        currentEdge = currentEdge->next();
//    } while (currentEdge != mOuterEdge);
    return sum/static_cast<float>(count);
}

    
void FaceNode::Invalidate(bool recursively)
{
    //if (mInvalid) return;
    
    Node::Invalidate(recursively);
    mPolygonPrimitive.Invalidate();
    
//    if (recursively) {
//        Edge* currentEdge = mOuterEdge;
//        do {
//            currentEdge->originNode()->Invalidate(true);
//            currentEdge = currentEdge->next();
//        } while (currentEdge != mOuterEdge);
//    }
}
    
void FaceNode::PointNodes(std::vector<Node*>& result) const
{
//    Node::PointNodes(result);
//    Edge* currentEdge = mOuterEdge;
//    do {
//        result.push_back(currentEdge->originNode());
//        currentEdge = currentEdge->next();
//    } while (currentEdge != mOuterEdge);

}
    
void FaceNode::Transform(const glm::mat4& transform)
{
//    Edge* currentEdge = mOuterEdge;
//    do {
//        currentEdge->originNode()->Transform(transform);
//        currentEdge = currentEdge->next();
//    } while (currentEdge != mOuterEdge);
}
    
glm::vec3 FaceNode::SurfaceNormal() const
{
//    Edge* currentEdge = mOuterEdge;
//    int counter = 0;
//    
    std::vector<glm::vec3> points;
//    points.reserve(3);
//    do {
//        points.push_back(currentEdge->origin());
//        currentEdge = currentEdge->next();
//        counter++; 
//        
//    } while (counter < 3);
    Triangle triangle(points);
    return triangle.SurfaceNormal();
    
}

    
//std::vector<Edge*> FaceNode::GetEdges() const
//{
//    std::vector<Edge*> result;
//    Edge* currentEdge = mOuterEdge;
//    do {
//        result.push_back(currentEdge);
//        currentEdge = currentEdge->next();
//    } while (currentEdge != mOuterEdge);
//    return result;
//}
    
    
std::vector<PointNode*> FaceNode::GetPointNodes() const
{
    std::vector<PointNode*> result;
//    Edge* currentEdge = mOuterEdge;
//    do {
//        result.push_back(currentEdge->originNode());
//        currentEdge = currentEdge->next();
//    } while (currentEdge != mOuterEdge);
    return result;
}

std::string FaceNode::Description() const
{
    std::string description = "";
    return description;
}

}
