
#include <Graph/PointNode.h>
#include <Graph/BodyNode.h>
#include <Processing/ModelEditor.h>
#include <Interaction/ExtrudeInteraction.h>
#include <Snapping/SnappingQueue.h>

namespace ftr {
    
ExtrudeInteraction::ExtrudeInteraction(ModelEditor& modelEditor, const Viewport& viewport)
:mModelEditor(modelEditor)
,mActive(false)
,mStartPoint(NULL)
,mEndPoint(NULL)
{
    mSnappingQueue = new SnappingQueue(viewport, *modelEditor.picker(), *modelEditor.modelTree());
    mPointSnap = new PointSnap(viewport, *modelEditor.picker(), *modelEditor.modelTree());
}

ExtrudeInteraction::~ExtrudeInteraction()
{
    FT_DELETE(mSnappingQueue);
    FT_DELETE(mPointSnap);
}

#pragma mark Instance

void ExtrudeInteraction::Render(Layer& layer)
{
    Node::Render(layer);
    linePrimitive.mBegin = mStart;
    linePrimitive.mEnd = mEnd;
    
    const glm::vec3 line = mEnd - mStart;
    
    glm::vec3 lineVector = glm::vec3(line.x, line.y, line.z);
    
    static glm::vec3 normalX = glm::vec3(1.0f, 0.0f, 0.0f);
    static glm::vec3 normalY = glm::vec3(0.0f, 1.0f, 0.0f);
    static glm::vec3 normalZ = glm::vec3(0.0f, 0.0f, 1.0f);
    
    glm::vec3 projX = glm::proj(lineVector, normalX);
    glm::vec3 projY = glm::proj(lineVector, normalY);
    glm::vec3 projZ = glm::proj(lineVector, normalZ);
    
    if (glm::length(projX) == glm::length(lineVector)) {
        linePrimitive.mColor = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else if (glm::length(projY) == glm::length(lineVector)) {
        linePrimitive.mColor = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else if (glm::length(projZ) == glm::length(lineVector)) {
        linePrimitive.mColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    } else {
        linePrimitive.mColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }
    
    linePrimitive.Invalidate();
    layer.AddPrimitive(linePrimitive);
}

void ExtrudeInteraction::Begin()
{
    if (!mActive) {
        mActive = true;
        mModelEditor.activeBody()->AddNode(this);
        
        mEndPoint = NULL;
        mStartPoint = NULL;
        
        mEnd = glm::vec3();
        mStart = glm::vec3();
        
    }
}

void ExtrudeInteraction::Step()
{
    if (mActive) {
        mActive = false;
        mModelEditor.activeBody()->RemoveNode(this);
        
        if (!mStartPoint) {
            mPointSnap->setStartScene(mStart, true);
            PointNode* snappedPoint = mPointSnap->SnappedPoint();
            if (snappedPoint) {
                mStartPoint = snappedPoint;
            } else {
                mStartPoint = mModelEditor.CreatePoint(mStart);
            }
            
        }
        
        if (!mEndPoint) {
            mPointSnap->setStartScene(mEnd, true);
            PointNode* snappedPoint = mPointSnap->SnappedPoint();
            if (snappedPoint) {
                mEndPoint = snappedPoint;
            } else {
                mEndPoint = mModelEditor.CreatePoint(mEnd);
            }
            
        }
        
        mModelEditor.CreateLine(mStartPoint, mEndPoint);
        mStartPoint = mEndPoint;
        mEndPoint = NULL;
    }
}

void ExtrudeInteraction::Finish()
{
    mActive = false;
}

void ExtrudeInteraction::setStart(const glm::vec2& start)
{
#ifndef TEST
    Viewport::AddDebugPoint(start);
#endif
    
    mSnappingQueue->setStartViewport(start, true);
    mSnappingQueue->setEndViewport(start, true);
    
    mStart = mSnappingQueue->Snapped();
    mSnappingQueue->setStartScene(mStart, true);
}

void ExtrudeInteraction::setEnd(const glm::vec2& endViewport)
{
    mSnappingQueue->setEndViewport(endViewport, true);
    
    mEnd = mSnappingQueue->Snapped();
}

    
    
}
