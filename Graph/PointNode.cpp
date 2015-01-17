
#include <Graph/PointNode.h>
#include <Graph/FaceNode.h>
#include <Graph/LineNode.h>
#include <Processing/Octree.h>



namespace ftr {

const float PointNode::c_fR = 5.0f;


PointNode::PointNode()
    :mOctreeLeaf(NULL)
    ,mIsActive(false)
    ,mVisited(false)
    ,mName("")
{
    
}
    
PointNode::~PointNode()
{
}
    

PointNode::PointNode(glm::vec3 origin)
:mOrigin(origin)
    ,mIsActive(false)
    ,mVisited(false)
    ,mName("")
    
{
    PointNode();
}
    
    
void PointNode::Transform(const glm::mat4& transform)
{
    glm::vec4 vec(mOrigin.x, mOrigin.y, mOrigin.z, 1.0f);
    vec = transform * vec;
    mOrigin = glm::vec3(vec.x, vec.y, vec.z);
}
    
void PointNode::Render(Layer& layer)
{
    Node::Render(layer);
    primitive.mPosition = mOrigin;
    primitive.mColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    primitive.setOption(Primitive::kUseDepth, false);
    layer.AddPrimitive(primitive);
}
    
void PointNode::Invalidate(bool recursively)
{
//    if (mInvalid) return;
    
    Node::Invalidate(recursively);
}
    
void PointNode::PointNodes(std::vector<Node*>& result)
{
    Node::PointNodes(result);
    result.push_back(reinterpret_cast<Node*>(this));
}

bool PointNode::OctreeLeafIsInvalid() const
{
    if (mOctreeLeaf) {
        return !mOctreeLeaf->Box().Contains(mOrigin);
    }
    return false;
}
    
    
std::string PointNode::Description() const
{
    return mName;
}

    
}
