
#include <Interaction/RotationInteraction.h>
#include <Model/ModelEditor.h>

namespace ftr {

RotationInteraction::RotationInteraction(ModelEditor& ModelEditor)
:mModelEditor(ModelEditor)
,mActive(false)
{}

void RotationInteraction::Render()
{
    
}

#pragma mark Instance

void RotationInteraction::setStart(glm::vec3 start)
{
    mStart = start;
}

void RotationInteraction::setEnd(glm::vec3 end)
{
    mEnd = end;
    //assert(mModelEditor.SelectedNode()->Type() == Node::kLine);
    //mModelEditor.SelectedNode()->Transform(Transformation::Rotate(mEnd - mStart));
    mStart = end;
}

}