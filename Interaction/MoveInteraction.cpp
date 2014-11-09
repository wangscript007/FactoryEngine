
#include <Interaction/MoveInteraction.h>
#include <Processing/ModelEditor.h>
#include <Scene/Picker.h>
#include <Scene/Camera.h>
#include <Geometry/Triangle.h>

namespace ftr {

MoveInteraction::MoveInteraction(ModelEditor& ModelEditor, const Viewport& viewport)
:mModelEditor(ModelEditor),
mViewport(viewport),
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
    mModelEditor.Select(point);
}
    
void MoveInteraction::Select(Node* node)
{
    mStart = mViewport.CoordsAt(node->Center());
    mModelEditor.Select(node);
}
    
void MoveInteraction::MoveTo(const glm::vec2& targetPoint)
{
    if (!mModelEditor.selectedNode()) return;
    
    mTarget = targetPoint;
    Triangle viewportPlane = mViewport.Plane();
    glm::vec3 offset = mModelEditor.selectedNode()->Center() - viewportPlane.Center();
    viewportPlane.Translate(offset);
    
    Segment startRay = mViewport.RayAtPoint(mStart);
    Segment endRay = mViewport.RayAtPoint(mTarget);
    
    glm::vec3 startIntersection;
    Segment::IntersectionSituation startSituation = startRay.IntersectionWithTriangle(viewportPlane, startIntersection);
    assert(startSituation != Segment::kIntersectionSituationInvalid);
    
    glm::vec3 endIntersection;
    Segment::IntersectionSituation endSituation = endRay.IntersectionWithTriangle(viewportPlane, endIntersection);
    assert(endSituation != Segment::kIntersectionSituationInvalid);
    
    glm::vec3 distance = endIntersection - startIntersection;
    
    mModelEditor.Move(distance);
    
    mStart = mTarget;
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
