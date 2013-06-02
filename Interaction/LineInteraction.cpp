
#include <Model/PointNode.h>
#include <Interaction/LineInteraction.h>
#include <Model/ModelEditor.h>

namespace ftr {

LineInteraction::LineInteraction(ModelEditor& ModelEditor)
    :mModelEditor(ModelEditor)
    ,mActive(false)
    ,mStartPoint(NULL)
    ,mEndPoint(NULL)
{

}

#pragma mark Instance

void LineInteraction::Render(Layer& layer)
{
    Node::Render(layer);
    linePrimitive.mBegin = mStart;
    linePrimitive.mEnd = mEnd;
    linePrimitive.color.set(1.0f, 1.0f, 1.0f);
    layer.AddPrimitive(linePrimitive);
}

void LineInteraction::Begin()
{
    if (!mActive) {
        mActive = true;
        mModelEditor.SelectedNode()->AddNode(this);
        mEndPoint = NULL;
        mStartPoint = NULL;
        mEnd = Vec3();
        mStart = Vec3();
    }
}

void LineInteraction::Step()
{
    if (mActive) {
        mActive = false;
        mModelEditor.SelectedNode()->RemoveNode(this);
        if (!mStartPoint) {
            mStartPoint = mModelEditor.CreatePoint(mStart);
        }
        if (!mEndPoint) {
            mEndPoint = mModelEditor.CreatePoint(mEnd);
        };
        mModelEditor.CreateLine(mStartPoint, mEndPoint);
        mStartPoint = mEndPoint;
        mEndPoint = NULL;
        
    }
}

void LineInteraction::End()
{
    mActive = false;
}

void LineInteraction::setEnd(Vec3 end)
{
    PointNode* pNearPoint = mModelEditor.NearestPointToCenterInSphere(Sphere(end, 0.5f));
    if (pNearPoint) {
        mEnd = pNearPoint->mOrigin;
        mEndPoint = pNearPoint;
    } else {
        mEnd = end;
        mEndPoint = NULL;
    }
}

void LineInteraction::setStart(Vec3 start)
{
    PointNode* pNearPoint = mModelEditor.NearestPointToCenterInSphere(Sphere(start, 0.5f));
    if (pNearPoint) {
        mStart = pNearPoint->mOrigin;
        mStartPoint = pNearPoint;
    } else {
        mStart = start;
        mStartPoint = NULL;
    }
}
    
}
