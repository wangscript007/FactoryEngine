
#include <Model/ModelEditor.h>
#include <Interaction/InteractionProvider.h>
#include <Interaction/RectangleInteraction.h>
#include <Interaction/LineInteraction.h>
#include <Interaction/MoveInteraction.h>
#include <Interaction/RotationInteraction.h>
#include <Interaction/ScaleInteraction.h>

namespace ftr {

InteractionProvider::InteractionProvider(ModelEditor& ModelEditor)
    :mModelEditor(ModelEditor)
{
    mRectangleInteraction = new class RectangleInteraction(mModelEditor);
    mLineInteraction = new class LineInteraction(mModelEditor);
    mMoveInteraction = new class MoveInteraction(mModelEditor);
    mRotationInteraction = new class RotationInteraction(mModelEditor);
    mScaleInteraction = new class ScaleInteraction(mModelEditor);
}

InteractionProvider::~InteractionProvider()
{
    FT_DELETE(mRectangleInteraction);
    FT_DELETE(mLineInteraction);
    FT_DELETE(mMoveInteraction);
    FT_DELETE(mRotationInteraction);
    FT_DELETE(mScaleInteraction);
}

}