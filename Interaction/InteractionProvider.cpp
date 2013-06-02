
#include <Model/ModelEditor.h>
#include <Scene/Camera.h>
#include <Interaction/InteractionProvider.h>
#include <Interaction/RectangleInteraction.h>
#include <Interaction/LineInteraction.h>
#include <Interaction/MoveInteraction.h>
#include <Interaction/RotationInteraction.h>
#include <Interaction/ScaleInteraction.h>
#include <Interaction/CameraInteraction.h>


namespace ftr {

InteractionProvider::InteractionProvider(ModelEditor& modelEditor, Camera& camera)
{
    mRectangleInteraction = new class RectangleInteraction(modelEditor);
    mLineInteraction = new class LineInteraction(modelEditor);
    mMoveInteraction = new class MoveInteraction(modelEditor);
    mRotationInteraction = new class RotationInteraction(modelEditor);
    mScaleInteraction = new class ScaleInteraction(modelEditor);
    mCameraInercation = new class CameraInteraction(camera);
}

InteractionProvider::~InteractionProvider()
{
    FT_DELETE(mRectangleInteraction);
    FT_DELETE(mLineInteraction);
    FT_DELETE(mMoveInteraction);
    FT_DELETE(mRotationInteraction);
    FT_DELETE(mScaleInteraction);
    FT_DELETE(mCameraInercation);
}

}