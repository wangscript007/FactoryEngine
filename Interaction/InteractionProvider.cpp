
#include <Processing/ModelEditor.h>
#include <Scene/Camera.h>
#include <Interaction/InteractionProvider.h>
#include <Interaction/RectangleInteraction.h>
#include <Interaction/LineInteraction.h>
#include <Interaction/MoveInteraction.h>
#include <Interaction/RotationInteraction.h>
#include <Interaction/ScaleInteraction.h>
#include <Interaction/CameraInteraction.h>
#include <Interaction/ExtrudeInteraction.h>
#include <Interaction/SelectInteraction.h>


namespace ftr {

InteractionProvider::InteractionProvider(ModelEditor& modelEditor, Camera& camera)
{
    mRectangleInteraction = new class RectangleInteraction(modelEditor);
    mLineInteraction = new class LineInteraction(modelEditor, camera.viewport());
    mSelectInteraction = new class SelectInteraction(modelEditor, camera.viewport());
    mExtrudeInteraction = new class ExtrudeInteraction(modelEditor, camera.viewport());
    mMoveInteraction = new class MoveInteraction(modelEditor);
    mRotationInteraction = new class RotationInteraction(modelEditor);
    mScaleInteraction = new class ScaleInteraction(modelEditor);
    mCameraInteraction = new class CameraInteraction(camera);
}

InteractionProvider::~InteractionProvider()
{
    FT_DELETE(mRectangleInteraction);
    FT_DELETE(mLineInteraction);
    FT_DELETE(mExtrudeInteraction);
    FT_DELETE(mSelectInteraction);
    FT_DELETE(mMoveInteraction);
    FT_DELETE(mRotationInteraction);
    FT_DELETE(mScaleInteraction);
    FT_DELETE(mCameraInteraction);
}

}