
#include <Interaction/ScaleInteraction.h>
#include <Model/ModelManager.h>
#include <Math/Transformation.h>

namespace ftr {


ScaleInteraction::ScaleInteraction(ModelManager& modelManager)
:mModelManager(modelManager)
,mActive(false)
{}

void ScaleInteraction::Render()
{
    
}

#pragma mark Instance

void ScaleInteraction::setStart(Vec3 start)
{
    mStart = start;
}

void ScaleInteraction::setEnd(Vec3 end)
{
    mEnd = end;
    assert(mModelManager.SelectedNode()->Type() == Node::kLine);
    Vec3 scale = mEnd - mStart;
    scale.mX = std::min(std::max(scale.mX, 1.0f), 2.0f);
    scale.mY = std::min(std::max(scale.mY, 1.0f), 2.0f);
    scale.mZ = std::min(std::max(scale.mZ, 1.0f), 2.0f);
    scale.set(0.99f, 1.001f, 1.001f);
    mModelManager.SelectedNode()->Transform(Transformation::Scale(scale));
    mStart = end;
}
    
}

