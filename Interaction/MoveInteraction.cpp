
#include <Interaction/MoveInteraction.h>
#include <Processing/ModelEditor.h>
#include <Scene/Picker.h>
#include <Scene/Camera.h>
#include <Geometry/Triangle.h>

namespace ftr {

MoveInteraction::MoveInteraction(ModelEditor& ModelEditor, Camera& camera)
:mModelEditor(ModelEditor),
mCamera(camera),
mActive(false)
{}

void MoveInteraction::Render(Layer &layer)
{
    Node::Render(layer);
}

#pragma mark Instance
    
void MoveInteraction::Select(const glm::vec2& point)
{
    mStart = point;
    Node* node = mModelEditor.picker()->Pick(point);
    if (node && node != mSelectedNode) {
        if (mSelectedNode) {
            mSelectedNode->setSelected(false);
        }
        mSelectedNode = node;
        mSelectedNode->setSelected(true);
    }
}
    
void MoveInteraction::MoveTo(const glm::vec2& targetPoint)
{
    mTarget = targetPoint;
    const Viewport& viewport = mCamera.viewport();
    Triangle viewportPlane = viewport.Plane();
    glm::vec3 offset = viewportPlane.Center() - mSelectedNode->Center();
    viewportPlane.Translate(offset);
    
    Segment startRay = viewport.RayAtPoint(mStart);
    Segment endRay = viewport.RayAtPoint(mTarget);
    
    glm::vec3 startIntersection;
    Segment::IntersectionSituation startSituation = startRay.IntersectionWithTriangle(viewportPlane, startIntersection);
    assert(startSituation != Segment::kIntersectionSituationInvalid);
    
    glm::vec3 endIntersection;
    Segment::IntersectionSituation endSituation = endRay.IntersectionWithTriangle(viewportPlane, endIntersection);
    assert(endSituation != Segment::kIntersectionSituationInvalid);
    
    glm::vec3 distance = endIntersection - startIntersection;
    
    mSelectedNode->Transform(glm::translate(distance));
    
}
    
void MoveInteraction::TurnOn()
{
    mModelEditor.picker()->setOn(true);
}

void MoveInteraction::TurnOff()
{
    mModelEditor.picker()->setOn(false);
}

}
