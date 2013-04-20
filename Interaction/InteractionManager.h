
#pragma once

namespace ftr {

class RectangleInteraction;
class LineInteraction;
class MoveInteraction;
class RotationInteraction;
class ScaleInteraction;
class ModelManager;

class InteractionManager
{
public:
    InteractionManager(ModelManager& modelManager);
    virtual ~InteractionManager();
    
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
    ModelManager& mModelManager;
};

}