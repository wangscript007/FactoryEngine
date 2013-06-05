
#pragma once

namespace ftr {

class RectangleInteraction;
class LineInteraction;
class MoveInteraction;
class RotationInteraction;
class ScaleInteraction;
class ModelEditor;
class CameraInteraction;
class Camera;

class InteractionProvider
{
public:
    InteractionProvider(ModelEditor& modelEditor, Camera& camera);
    virtual ~InteractionProvider();
    
    RectangleInteraction* RectangleInteraction() const { return mRectangleInteraction; }
    LineInteraction* LineInteraction() const { return mLineInteraction; }
    MoveInteraction* MoveInteraction() const { return mMoveInteraction; }
    RotationInteraction* RotationInteraction() const { return mRotationInteraction; }
    ScaleInteraction* ScaleInteraction() const { return mScaleInteraction; }
    CameraInteraction* CameraInteraction() const { return mCameraInteraction; }
    
private:
    class RectangleInteraction* mRectangleInteraction;
    class LineInteraction* mLineInteraction;
    class MoveInteraction* mMoveInteraction;
    class RotationInteraction* mRotationInteraction;
    class ScaleInteraction* mScaleInteraction;
    class CameraInteraction* mCameraInteraction;
};

}