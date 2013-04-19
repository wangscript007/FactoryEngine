
#include <Interaction/MoveInteraction.h>
#include <Managers/ModelManager.h>
#include <Math/Transformation.h>

namespace ftr {

MoveInteraction::MoveInteraction(ModelManager& modelManager)
:mModelManager(modelManager)
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
    assert(mModelManager.SelectedNode()->Type() == Node::kLine);
    mModelManager.SelectedNode()->Transform(Transformation::Move(mEnd - mStart));
    mStart = end;
}

}
