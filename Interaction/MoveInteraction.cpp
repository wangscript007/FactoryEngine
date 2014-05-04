
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
