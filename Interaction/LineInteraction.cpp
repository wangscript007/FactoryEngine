
#include <Model/Point.h>
#include <Interaction/LineInteraction.h>
#include <Managers/ModelManager.h>

namespace ftr {

LineInteraction::LineInteraction(ModelManager& modelManager)
    :mModelManager(modelManager)
    ,mActive(false)
    ,mStartPoint(NULL)
    ,mEndPoint(NULL)
{}

#pragma mark Instance

void LineInteraction::Render()
{
    Node::Render();
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glLineWidth(1);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    {
        glVertex3d(mStart.mX,
                   mStart.mY,
                   mStart.mZ);
        glVertex3d(mEnd.mX,
                   mEnd.mY,
                   mEnd.mZ);
    }
    glEnd();
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
    Point* pNearPoint = mModelManager.NearestPointToCenterInSphere(Sphere(end, 0.5f));
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
    Point* pNearPoint = mModelManager.NearestPointToCenterInSphere(Sphere(start, 0.5f));
    if (pNearPoint) {
        mStart = pNearPoint->mOrigin;
        mStartPoint = pNearPoint;
    } else {
        mStart = start;
        mStartPoint = NULL;
    }
}
    
}
