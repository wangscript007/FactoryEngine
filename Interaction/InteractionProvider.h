
#pragma once

namespace ftr {

class RectangleInteraction;
class LineInteraction;
class MoveInteraction;
class RotationInteraction;
class ScaleInteraction;
class ModelEditor;

class InteractionProvider
{
public:
    InteractionProvider(ModelEditor& ModelEditor);
    virtual ~InteractionProvider();
    
    RectangleInteraction* RectangleInteraction() const { return mRectangleInteraction; }
    LineInteraction* LineInteraction() const { return mLineInteraction; }
    MoveInteraction* MoveInteraction() const { return mMoveInteraction; }
    RotationInteraction* RotationInteraction() const { return mRotationInteraction; }
    ScaleInteraction* ScaleInteraction() const { return mScaleInteraction; }
    
private:
    class RectangleInteraction* mRectangleInteraction;
    class LineInteraction* mLineInteraction;
    class MoveInteraction* mMoveInteraction;
    class RotationInteraction* mRotationInteraction;
    class ScaleInteraction* mScaleInteraction;
    ModelEditor& mModelEditor;
};

}