
#include <Interaction/MoveInteraction.h>
#include <Model/ModelEditor.h>
#include <Math/Transformation.h>

namespace ftr {

MoveInteraction::MoveInteraction(ModelEditor& ModelEditor)
:mModelEditor(ModelEditor)
,mActive(false)
{}

void MoveInteraction::Render()
{
    
}

#pragma mark Instance

void MoveInteraction::setStart(Vec3 start)
{
    mStart = start;
}

void MoveInteraction::setEnd(Vec3 end)
{
    mEnd = end;
    assert(mModelEditor.SelectedNode()->Type() == Node::kLine);
    mModelEditor.SelectedNode()->Transform(Transformation::Translate(mEnd - mStart));
    mStart = end;
}

}
