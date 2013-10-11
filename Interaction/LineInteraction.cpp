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
    
    const glm::vec3 line = mEnd - mStart;
    
    glm::vec3 lineVector = glm::vec3(line.x, line.y, line.z);
    
    glm::vec3 normalX = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 normalY = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 normalZ = glm::vec3(0.0f, 0.0f, 1.0f);
    
    glm::vec3 projX = glm::proj(lineVector, normalX);
    glm::vec3 projY = glm::proj(lineVector, normalY);
    glm::vec3 projZ = glm::proj(lineVector, normalZ);
    
    if (glm::length(projX) == glm::length(lineVector)) {
        linePrimitive.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else if (glm::length(projY) == glm::length(lineVector)) {
        linePrimitive.color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    }
    else if (glm::length(projZ) == glm::length(lineVector)) {
        linePrimitive.color = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    } else {
        linePrimitive.color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    linePrimitive.Invalidate();
    layer.AddPrimitive(linePrimitive);
}

void LineInteraction::Begin()
{
    if (!mActive) {
        mActive = true;
        mModelEditor.SelectedNode()->AddNode(this);
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

void LineInteraction::setEnd(glm::vec3 end)
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
    
void LineInteraction::setEndViewport(const glm::vec2& endViewport)
{
    glm::vec3 end;
    const glm::vec3& suggestedEnd =  mInteractionAssitant.AxisAlignedViewport(mStart, endViewport);
    
    if (mStart == suggestedEnd) {
        //end = Picker::Scene(glm::vec3(endViewport.x, endViewport.y, 0.0f));
    } else {
        end = suggestedEnd;
    }
    
    PointNode* pNearPoint = mModelEditor.NearestPointToCenterInSphere(Sphere(end, 0.5f));
    if (pNearPoint) {
        mEnd = pNearPoint->mOrigin;
        mEndPoint = pNearPoint;
    } else {
        mEnd = end;
        mEndPoint = NULL;
    }
}


void LineInteraction::setStart(glm::vec3 start)
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
