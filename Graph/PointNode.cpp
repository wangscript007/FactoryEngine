
#include <Graph/PointNode.h>
#include <Graph/FaceNode.h>
#include <Graph/LineNode.h>
#include <Processing/Octree.h>
#include <Graph/Vertex.h>
#include <Graph/Edge.h>


namespace ftr {

const float PointNode::c_fR = 5.0f;


PointNode::PointNode()
    :mOctreeLeaf(NULL)
    ,mName("")
    ,mVertex(Vertex(glm::vec3(), *this))
{
    
}
    
PointNode::~PointNode()
{
}
    

PointNode::PointNode(glm::vec3 origin)
    :mIsActive(false)
    ,mName("")
    ,mVertex(Vertex(origin, *this))
{
}
    
    
void PointNode::Transform(const glm::mat4& transform)
{
    glm::vec4 vec(mVertex.mOrigin, 1.0f);
    vec = transform * vec;
    mVertex.mOrigin = glm::vec3(vec);
}
    
void PointNode::Render(Layer& layer)
{
    Node::Render(layer);
    primitive.mPosition = mVertex.mOrigin;
    primitive.mColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    primitive.setOption(Primitive::kUseDepth, false);
    layer.AddPrimitive(primitive);
}
    
void PointNode::Invalidate(bool recursively)
{
    if (mInvalid) return;
    
    Node::Invalidate(recursively);
    
    if (recursively) {
        for (Edge* edge : mVertex.mEdges) {
            edge->mLineNode->Invalidate(false);
        }
    }
    
}
    
bool PointNode::IsConnectedTo(const PointNode& target)
{
    return mVertex.IsConnectedTo(target.mVertex);
}
    
void PointNode::PointNodes(std::vector<Node*>& result)
{
    Node::PointNodes(result);
    result.push_back(reinterpret_cast<Node*>(this));
}
    
#pragma mark - Octree
    
bool PointNode::OctreeLeafIsInvalid() const
{
    if (mOctreeLeaf) {
        return !mOctreeLeaf->Box().Contains(mVertex.mOrigin);
    }
    return false;
}

std::string PointNode::Description() const
{
    return mName;
}

    
}
