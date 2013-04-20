
#include <Interaction/RotationInteraction.h>
#include <Model/ModelManager.h>
#include <Math/Transformation.h>

namespace ftr {

RotationInteraction::RotationInteraction(ModelManager& modelManager)
:mModelManager(modelManager)
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
    assert(mModelManager.SelectedNode()->Type() == Node::kLine);
    mModelManager.SelectedNode()->Transform(Transformation::Rotate(mEnd - mStart));
    mStart = end;
}

}