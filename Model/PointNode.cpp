
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
    
#pragma mark - List
    
PointNode::Iterator PointNode::Begin() const
{
    assert(mEdge);
    return IteratorFromEdge(mEdge);
}

PointNode::Iterator PointNode::End() const
{
    return Iterator(*this, NULL);
}
    
PointNode::Iterator PointNode::IteratorFromEdge(Edge* edge) const
{
    if (edge->originNode() != this) {
        edge = edge->twin();
        assert(edge->originNode() == this);
    }
    return Iterator(*this, edge);
}


void PointNode::Insert(PointNode::Iterator position, ftr::Edge& edge)
{
    if (position == End()) {
        position = Begin();
    }
    ftr::Edge* posEdge = (*position);
    ftr::Edge* insertEdge = NULL;
    if (edge.originNode() != this) {
        insertEdge = edge.twin();
    } else {
        insertEdge = &edge;
    }
    assert(insertEdge->originNode() == this);
    assert(posEdge->originNode() == this);
    
    printf("inserting edge %s at position %s\n", edge.Name().c_str(), posEdge->Name().c_str());

    if (posEdge->prev()) {
        posEdge->prev()->ConnectToNext(insertEdge);
    } else {
        posEdge->twin()->ConnectToNext(insertEdge);
    }
    insertEdge->twin()->ConnectToNext(posEdge);
    
    if (position == Begin()) {
        // Marking as new begin
        mEdge = insertEdge;
    }
}

void PointNode::Remove(PointNode::Iterator position)
{
    assert(position != End());
    ftr::Edge* posEdge = (*position);
    
    ftr::Edge* prev = posEdge->prev();
    ftr::Edge* next = posEdge->twin()->next();
    
    
  
    if (position == Begin()) {
        // mark new begin or NULL if last edge was removed
        mEdge = next;
    }
    if (prev && next) {
        
        if (prev->twin() != next) {
            // true, if there are more than two edges
            prev->ConnectToNext(next);
        } else {
            prev->DisconnectNext();
            next->DisconnectPrev();
        }
    }
    posEdge->DisconnectPrev();
    posEdge->twin()->DisconnectNext();

}
    
    
#pragma mark - Connecting
    
// Work with connections from both directions
PointNode::ConnectionResult PointNode::ConnectTo(PointNode* other, bool skipTraversal)
{
    ConnectionResult result;
    ftr::Edge* newEdge = new ftr::Edge(this);
    ftr::Edge* newEdgeTwin = new ftr::Edge(other);
    newEdge->MakeTwinsWith(newEdgeTwin);
    result.edge = newEdge;
    
    if (mEdge) {
        if (!skipTraversal) {
            FaceTraversal traversal(*newEdgeTwin);
            traversal.Find();
            if (traversal.FaceEdges().size()) {
                result.faceA = new FaceNode(traversal.FaceEdges());
            } else {
                result.faceA = NULL;
                Insert(End(), *newEdgeTwin);
            }

        }
    } else {
        mEdge = newEdge;
    }
    
    if (other->mEdge) {
        if (!skipTraversal) {
            FaceTraversal traversal(*newEdge);
            traversal.Find();
            if (traversal.FaceEdges().size()) {
                result.faceB = new FaceNode(traversal.FaceEdges());
            } else {
                result.faceB = NULL;
                other->Insert(other->End(), *newEdge);
            }
            
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

    
std::string PointNode::Description() const
{
    // Node 1:{e12, e12, e13}
    std::string description = "Node " + mName + ": {";
    for(PointNode::Iterator it = Begin(); it != End(); ++it) {
        description += (*it)->Name() + "; ";
    }
    description += "END}";
    return description;
}

    
}
