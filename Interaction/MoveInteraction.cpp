
#include <Interaction/MoveInteraction.h>
#include <Processing/ModelEditor.h>
#include <Scene/Picker.h>

namespace ftr {

MoveInteraction::MoveInteraction(ModelEditor& ModelEditor)
:mModelEditor(ModelEditor)
,mActive(false)
{}

void MoveInteraction::Render()
{
    
}

#pragma mark Instance

void MoveInteraction::setStart(glm::vec3 start)
{
    mStart = start;
}

void MoveInteraction::setEnd(glm::vec3 end)
{
    mEnd = end;
    mStart = end;
}
    
void MoveInteraction::Select(const glm::vec2& point)
{
    Node* node = mModelEditor.picker()->Pick(point);
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
