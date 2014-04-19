
#include <Model/PointNode.h>
#include <Processing/ModelEditor.h>
#include <Interaction/LineInteraction.h>
#include <Snapping/SnappingQueue.h>

namespace ftr {

LineInteraction::LineInteraction(ModelEditor& modelEditor, const Viewport& viewport)
    :mModelEditor(modelEditor)
    ,mActive(false)
    ,mStartPoint(NULL)
    ,mEndPoint(NULL)
    ,mViewport(&viewport)
{
    mSnappingQueue = new SnappingQueue(viewport, *modelEditor.ModelTree());
    mPointSnap = new PointSnap(viewport, *modelEditor.ModelTree());
}
    
LineInteraction::~LineInteraction()
{
    FT_DELETE(mSnappingQueue);
    FT_DELETE(mPointSnap);
}

#pragma mark Instance

void LineInteraction::Render(Layer& layer)
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
    linePrimitive.setOption(Primitive::kUseDepth, false);
    layer.AddPrimitive(linePrimitive);
}

void LineInteraction::Begin()
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

void LineInteraction::Step()
{
    if (mActive) {
        mActive = false;
        mModelEditor.activeBody()->RemoveNode(this);
        
        if (!mStartPoint) {
            mPointSnap->setStartScene(mStart, true);
            PointNode* snappedPoint = mPointSnap->SnappedPoint();
            if (snappedPoint && snappedPoint->ContainsFreeEdges()) {
                mStartPoint = snappedPoint;
            } else {
                mStartPoint = mModelEditor.CreatePoint(mStart);
            }
            
        }
        
        if (!mEndPoint) {
            mPointSnap->setStartScene(mEnd, true);
            PointNode* snappedPoint = mPointSnap->SnappedPoint();
            if (snappedPoint && snappedPoint->ContainsFreeEdges()) {
                mEndPoint = snappedPoint;
            } else {
                mEndPoint = mModelEditor.CreatePoint(mEnd);
            }
            
        }
        
        if (mStartPoint != mEndPoint) {
            mModelEditor.CreateLine(mStartPoint, mEndPoint);
            mStartPoint = mEndPoint;

        }
        mEndPoint = NULL;
    }
}

void LineInteraction::Finish()
{
    mActive = false;
}
    
void LineInteraction::setStart(const glm::vec2& start)
{
#ifndef TEST
    Viewport::AddDebugPoint(start);
#endif
    
    mSnappingQueue->setStartViewport(start, true);
    mSnappingQueue->setEndViewport(start, true);
    
    mStart = mSnappingQueue->Snapped();
    mSnappingQueue->setStartScene(mStart, true);
}
    
void LineInteraction::setEnd(const glm::vec2& endViewport)
{
    mSnappingQueue->setEndViewport(endViewport, true);
    
    mEnd = mSnappingQueue->Snapped();
    if (mEnd == mStart) {
        mEnd = mViewport->SceneCoordsAt(endViewport);
    }
    
}


    
}
