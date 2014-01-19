
#include <Model/PointNode.h>
#include <Model/Edge.h>
#include <Main/Log.h>

namespace ftr {

const float PointNode::c_fR = 5.0f;


PointNode::PointNode()
    :mOctreeLeaf(NULL)
    ,mEdge(NULL)
    ,mIsActive(false)
    ,mName("")
{
    
}
    
PointNode::~PointNode()
{
    if (mEdge) {
        assert(mEdge->twin()->originNode()->mEdge != mEdge);
        mEdge->twin()->originNode()->mEdge = NULL;
        mEdge->DeleteTwin();
        FT_DELETE(mEdge);
    }
}

PointNode::PointNode(glm::vec3 origin)
:mOrigin(origin)
    ,mEdge(NULL)
    ,mIsActive(false)
    ,mName("")
    
{
    PointNode();
}
    
Edge* PointNode::Begin() const
{
    return mEdge;
}
    
Edge* PointNode::End() const
{
    if (mEdge) {
        return mEdge->prev() ? mEdge->prev() : mEdge;
    } else {
        return NULL;
    }
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
    
// Work with connections from both directions
Edge* PointNode::ConnectTo(PointNode* other)
{
    ftr::Edge* newEdge = new ftr::Edge(this);
    ftr::Edge* newEdgeTwin = new ftr::Edge(other);
    newEdge->MakeTwinsWith(newEdgeTwin);
    
    if (mEdge) {
        newEdge->DoublyConnectCCWOrderedAtOrigin();
    } else {
        mEdge = newEdge;
    }
    
    if (other->mEdge) {
        newEdgeTwin->DoublyConnectCCWOrderedAtOrigin();
    } else {
        other->mEdge = newEdgeTwin;
    }
    return newEdge;
}
    
Edge* PointNode::FindOutgoingFreeEdge() const
{
    ftr::Edge* edge = mEdge;
    do {
        if (edge->originNode() == this) {
            if (edge->IsFree()) break;
        }
        
        if ((edge->originNode() == this) && edge->prev()) {
            edge = edge->prev();
        } else {
            edge = edge->twin();
        }
    } while (edge != mEdge);
    
    return edge->IsFree() ? edge : NULL;
}

    
    
    
}
