
#include <Interaction/RotationInteraction.h>
#include <Model/ModelEditor.h>
#include <Math/Transformation.h>

namespace ftr {

RotationInteraction::RotationInteraction(ModelEditor& ModelEditor)
:mModelEditor(ModelEditor)
,mActive(false)
{}

void RotationInteraction::Render()
{
    
}

#pragma mark Instance

void RotationInteraction::setStart(Vec3 start)
{
    mStart = start;
}

void RotationInteraction::setEnd(Vec3 end)
{
    mEnd = end;
    assert(mModelEditor.SelectedNode()->Type() == Node::kLine);
    mModelEditor.SelectedNode()->Transform(Transformation::Rotate(mEnd - mStart));
    mStart = end;
}

}