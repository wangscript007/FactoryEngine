
#include <Graph/FaceNode.h>
#include <Graph/LineNode.h>
#include <Graph/PointNode.h>
#include <Processing/PointNodeIterator.h>
#include <Graph/Edge.h>
#include <Geometry/Triangle.h>
#include <Processing/ColorPickingMapper.h>


namespace ftr {
    
    
FaceNode::~FaceNode()
{
    
}

    
FaceNode::FaceNode(const std::vector<Edge*>& edges)
{
    InitWithEdges(edges);
}
    
void FaceNode::InitWithEdges(const std::vector<Edge*>& edges)
{
    assert(edges.size() > 2);
    for (int i = 0; i < edges.size()-1; ++i) {
        Edge* currentEdge = edges[i]->twin();
        Edge* nextEdge = edges[i+1];
        OrderAscending(*nextEdge, *currentEdge);
    }
    OrderAscending(*edges.front(), *edges.back()->twin());
    assert(IsValid(edges));
    BoundByLoopWithEdge(*edges.front());

}
    
void FaceNode::Render(Layer& layer)
{
    Node::Render(layer);
    if (mSelected) {
        mPolygonPrimitive.mColor = glm::vec4(44/255.0f, 64/255.0f, 0.5f, 127/2555.0f);
    } else {
        mPolygonPrimitive.mColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
    }
    glm::vec3 color = glm::vec3(ColorPickingMapper::ColorFromInt(mPickingId));
    mPolygonPrimitive.mPickingColor = glm::vec4(color.x, color.y, color.z, 1.0f);
    Edge* currentEdge = mOuterEdge;
    mPolygonPrimitive.mVec.clear();
    do {
        mPolygonPrimitive.mVec.push_back(currentEdge->origin());
        if (!currentEdge->next()) {
            assert(false); // face is messed up!
        }
        currentEdge = currentEdge->next();
    } while (currentEdge != mOuterEdge);
    mPolygonPrimitive.setOption(Primitive::kUseDepth, true);
    layer.AddPrimitive(mPolygonPrimitive);
}
    
glm::vec3 FaceNode::Center() const
{
    glm::vec3 sum;
    int count = 0;
    Edge* currentEdge = mOuterEdge;
    do {
        count++;
        sum += currentEdge->originNode()->mOrigin;
        currentEdge = currentEdge->next();
    } while (currentEdge != mOuterEdge);
    return sum/static_cast<float>(count);
}

    
void FaceNode::Invalidate(bool recursively)
{
    if (mInvalid) return;
    
    Node::Invalidate(recursively);
    mPolygonPrimitive.Invalidate();
    
    if (recursively) {
        Edge* currentEdge = mOuterEdge;
        do {
            currentEdge->originNode()->Invalidate(true);
            currentEdge = currentEdge->next();
        } while (currentEdge != mOuterEdge);
    }
}
    
void FaceNode::Transform(const glm::mat4& transform)
{
    Edge* currentEdge = mOuterEdge;
    do {
        currentEdge->originNode()->Transform(transform);
        currentEdge = currentEdge->next();
    } while (currentEdge != mOuterEdge);
}
    
FaceNode::FaceNode(const std::vector<glm::vec3>& points)
{
    assert(points.size() > 2);
    
    std::vector<Edge*> edges;
    
    PointNode* startPointNode = new PointNode(points[0]);
    startPointNode->mName = "1";
    PointNode* lastPointNode = startPointNode;
    for (int i = 1; i < points.size(); ++i)
    {
        PointNode* currentPointNode = new PointNode(points[i]);
        
        std::stringstream ss;
        ss << i+1;
        currentPointNode->mName = ss.str();
        
        edges.push_back(lastPointNode->ConnectTo(currentPointNode, true).edge);
        lastPointNode = currentPointNode;
    }
    mOuterEdge = lastPointNode->ConnectTo(startPointNode, true).edge;
    edges.push_back(mOuterEdge);
    InitWithEdges(edges);
}
    
void FaceNode::OrderAscending(Edge& edge1, Edge& edge2)
{
    assert(edge1.originNode() == edge2.originNode());
    PointNode* currentNode = edge1.originNode();
    currentNode->Move(edge2, currentNode->IteratorFromEdge(&edge1));
}
    
bool FaceNode::IsValid(const std::vector<Edge*>& edges) const
{
    for(int i = 0; i < edges.size()-1; i++) {
        if (edges[i]->next() != edges[i+1]) {
            return false;
        }
    }
    if (edges.back()->next() != edges.front()) {
        return false;
    }
    return true;
}
    
bool FaceNode::IsValid() const
{
    int counter = 0;
    Edge* currentEdge = mOuterEdge;
    do {
        if (!currentEdge->next()) {
            return false;
        }
        currentEdge = currentEdge->next();
        counter++;
    } while ((currentEdge != mOuterEdge) && (counter < 1000));
    
    return currentEdge == mOuterEdge && (counter > 2);
}
    
glm::vec3 FaceNode::SurfaceNormal() const
{
    Edge* currentEdge = mOuterEdge;
    int counter = 0;
    
    std::vector<glm::vec3> points;
    do {
        points.push_back(currentEdge->origin());
        currentEdge = currentEdge->next();
        counter++;
        
    } while (counter < 3);
    Triangle triangle(points);
    return triangle.SurfaceNormal();
    
}

    
std::vector<Edge*> FaceNode::GetEdges() const
{
    std::vector<Edge*> result;
    Edge* currentEdge = mOuterEdge;
    do {
        result.push_back(currentEdge);
        currentEdge = currentEdge->next();
    } while (currentEdge != mOuterEdge);
    return result;
}
    
    
std::vector<PointNode*> FaceNode::GetPointNodes() const
{
    std::vector<PointNode*> result;
    Edge* currentEdge = mOuterEdge;
    do {
        result.push_back(currentEdge->originNode());
        currentEdge = currentEdge->next();
    } while (currentEdge != mOuterEdge);
    return result;
}

    

#pragma mark - Instance
    
void FaceNode::BoundByLoopWithEdge(Edge& outerEdge)
{
    mOuterEdge = &outerEdge;
    MarkIncidentFaceInLoopWithEdge(outerEdge);
}
    
void FaceNode::AddHoleBoundedByLoopWithEdge(Edge& innerEdge)
{
    mInnerEdges.push_back(&innerEdge);
    MarkIncidentFaceInLoopWithEdge(innerEdge);
}
    
void FaceNode::MarkIncidentFaceInLoopWithEdge(Edge& edge)
{
    Edge* currentEdge = &edge;
    do {
        currentEdge->mIncidentFace = this;
        printf("Mark %s\n", currentEdge->Name().c_str());
        currentEdge = currentEdge->next();
    } while ( currentEdge->IsFree() );
}
    

std::string FaceNode::Description() const
{
    std::string description = "";
    Edge* currentEdge = mOuterEdge;
    while (currentEdge->next() && (currentEdge->next() != mOuterEdge)) {
        currentEdge = currentEdge->next();
        description += currentEdge->originNode()->mName + "-";
    }
    description += currentEdge->next()->originNode()->mName;
    return description;
}

}
