
#include <Model/PointNode.h>
#include <Interaction/LineInteraction.h>
#include <Model/ModelManager.h>

namespace ftr {

LineInteraction::LineInteraction(ModelManager& modelManager)
    :mModelManager(modelManager)
    ,mActive(false)
    ,mStartPoint(NULL)
    ,mEndPoint(NULL)
{

}

#pragma mark Instance

void LineInteraction::Render(RenderBundle& renderBundle)
{
    Node::Render(renderBundle);
    linePrimitive.mBegin = mStart;
    linePrimitive.mEnd = mEnd;
    linePrimitive.color.set(1.0f, 1.0f, 1.0f);
    renderBundle.AddPrimitive(linePrimitive);
}

void LineInteraction::Begin()
{
    if (!mActive) {
        mActive = true;
        mModelManager.SelectedNode()->AddNode(this);
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
        mModelManager.SelectedNode()->RemoveNode(this);
        if (!mStartPoint) {
            mStartPoint = mModelManager.CreatePoint(mStart);
        }
        if (!mEndPoint) {
            mEndPoint = mModelManager.CreatePoint(mEnd);
        };
        mModelManager.CreateLine(mStartPoint, mEndPoint);
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
    PointNode* pNearPoint = mModelManager.NearestPointToCenterInSphere(Sphere(end, 0.5f));
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
    PointNode* pNearPoint = mModelManager.NearestPointToCenterInSphere(Sphere(start, 0.5f));
    if (pNearPoint) {
        mStart = pNearPoint->mOrigin;
        mStartPoint = pNearPoint;
    } else {
        mStart = start;
        mStartPoint = NULL;
    }
}
    
}
