
#include <Model/ModelManager.h>
#include <Interaction/InteractionManager.h>
#include <Interaction/RectangleInteraction.h>
#include <Interaction/LineInteraction.h>
#include <Interaction/MoveInteraction.h>
#include <Interaction/RotationInteraction.h>
#include <Interaction/ScaleInteraction.h>

namespace ftr {

InteractionManager::InteractionManager(ModelManager& modelManager)
    :mModelManager(modelManager)
{
    mRectangleInteraction = new class RectangleInteraction(mModelManager);
    mLineInteraction = new class LineInteraction(mModelManager);
    mMoveInteraction = new class MoveInteraction(mModelManager);
    mRotationInteraction = new class RotationInteraction(mModelManager);
    mScaleInteraction = new class ScaleInteraction(mModelManager);
}

InteractionManager::~InteractionManager()
{
    FT_DELETE(mRectangleInteraction);
    FT_DELETE(mLineInteraction);
    FT_DELETE(mMoveInteraction);
    FT_DELETE(mRotationInteraction);
    FT_DELETE(mScaleInteraction);
}

}