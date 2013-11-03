
#include <Model/PointNode.h>
#include <Model/HalfEdge.h>
#include <Main/Log.h>

namespace ftr {

const float PointNode::c_fR = 5.0f;


PointNode::PointNode()
    :mOctreeLeaf(NULL)
    ,mHalfEdge(NULL)
    ,mIsActive(false)
    ,mName("")
{
    
}
    
PointNode::~PointNode()
{
    if (mHalfEdge) {
        assert(mHalfEdge->twin()->originNode()->mHalfEdge != mHalfEdge);
        mHalfEdge->twin()->originNode()->mHalfEdge = NULL;
        mHalfEdge->DeleteTwin();
        FT_DELETE(mHalfEdge);
    }
}

PointNode::PointNode(glm::vec3 origin)
:mOrigin(origin)
    ,mHalfEdge(NULL)
    ,mIsActive(false)
    ,mName("")
    
{
    PointNode();
}

void PointNode::Transform(const glm::mat4& m4Transformation)
{
    //mOrigin *= m4Transformation;
}

#pragma mark - Instance

void PointNode::Render(Layer& layer)
{
    Node::Render(layer);
    primitive.mPosition = mOrigin;
    primitive.mColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    primitive.setOption(Primitive::kUseDepth, false);
    layer.AddPrimitive(primitive);
}
    
void PointNode::ConnectTo(PointNode* newNode)
{
    HalfEdge* prev = NULL;
    if (mHalfEdge) {
        prev = mHalfEdge->twin();
    }
    
    HalfEdge* next = NULL;
    if (newNode->mHalfEdge) {
        next = newNode->mHalfEdge;
    }
    
    mHalfEdge = new HalfEdge(this);
    HalfEdge* twin = new HalfEdge(newNode);
    
    newNode->mHalfEdge = twin;
    mHalfEdge->setTwin(twin);
    
    mHalfEdge->setPrev(prev);
    if (next) {
        next->setPrev(mHalfEdge);
    }
    
    if (mHalfEdge->prev()) {
        if (mHalfEdge->IsClockwiseFrom(*mHalfEdge->prev())) {
            mHalfEdge->Reverse();
        }
    }
}
    
    
}
