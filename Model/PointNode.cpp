
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
    
void PointNode::ConnectTo(PointNode* other)
{
    // Create new pair of half edges
    HalfEdge* newHalfEdge = new HalfEdge(this);
    HalfEdge* newHalfEdgeTwin = new HalfEdge(other);
    newHalfEdge->MakeTwinsWith(newHalfEdgeTwin);

    // Connect with previous edge
    if (mHalfEdge) {
        if (newHalfEdge->IsClockwiseCountingFrom(*mHalfEdge)) {
            newHalfEdgeTwin->ConnectToNext(mHalfEdge);
        } else {
            newHalfEdge->ConnectToNext(mHalfEdge);
        }
    } else {
        mHalfEdge = newHalfEdge;
    }
    
    // Connect to next edge
    if (other->mHalfEdge) {
        if (other->mHalfEdge->IsClockwiseCountingFrom(*newHalfEdge)) {
            newHalfEdgeTwin->ConnectToNext(other->mHalfEdge);
        } else {
            newHalfEdge->ConnectToNext(other->mHalfEdge);
        }
    } else {
        other->mHalfEdge = newHalfEdgeTwin;
    }
//    printf("%s \n", newHalfEdge->Description().c_str());
    
}

    
    
}
