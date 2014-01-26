
#include <Model/PointNode.h>
#include <Model/PointNodeIterator.h>
#include <Model/Edge.h>
#include <Main/Log.h>
#include <Model/FaceNode.h>
#include <Model/FaceTraversal.h>


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
    
PointNode::Iterator PointNode::Begin() const
{
    return Iterator(*this, mEdge);
}

PointNode::Iterator PointNode::End() const
{
    if (mEdge) {
        if (mEdge->prev()) {
            return Iterator(*this, mEdge->prev());
        } else {
            return Iterator(*this, mEdge->twin());
        }
    } else {
        Iterator(*this, NULL);
    }
}

void PointNode::Insert(PointNode::Iterator position, ftr::Edge& edge)
{
    if ((*position)->originNode() != this) {
        ++position;
    }
    ftr::Edge* itrEdge = (*position);
    
    if (itrEdge->prev()) {
        itrEdge->prev()->ConnectToNext(&edge);
    } else {
        itrEdge->twin()->ConnectToNext(&edge);
    }
    edge.twin()->ConnectToNext(itrEdge);
}

void PointNode::Erase(PointNode::Iterator position)
{
    // Fill in
}
    
// Work with connections from both directions
PointNode::ConnectionResult PointNode::ConnectTo(PointNode* other)
{
    ConnectionResult result;
    ftr::Edge* newEdge = new ftr::Edge(this);
    ftr::Edge* newEdgeTwin = new ftr::Edge(other);
    newEdge->MakeTwinsWith(newEdgeTwin);
    result.edge = newEdge;
    
    if (mEdge) {
        FaceTraversal traversal(*newEdgeTwin);
        traversal.Find();
        if (traversal.FaceEdges().size()) {
            result.faceA = new FaceNode(traversal.FaceEdges());
            Insert(PointNodeIterator(*other, traversal.FaceEdges().front()), *newEdgeTwin);
        } else {
            Insert(End(), *newEdgeTwin);
            result.faceA = NULL;
        }
    } else {
        mEdge = newEdge;
    }
    
    if (other->mEdge) {
        FaceTraversal traversal(*newEdge);
        traversal.Find();
        if (traversal.FaceEdges().size()) {
            result.faceB = new FaceNode(traversal.FaceEdges());
            Insert(PointNodeIterator(*this, traversal.FaceEdges().front()), *newEdge);
        } else {
            other->Insert(other->End(), *newEdge);
            result.faceB = NULL;
        }
    } else {
        other->mEdge = newEdgeTwin;
    }
    
    return result;
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
