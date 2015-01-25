
#include <Snapping/Snap.h>
#include <Scene/Viewport.h>
#include <Scene/Picker.h>
#include <Processing/ModelTree.h>

namespace ftr {
    
Snap::Snap(const Viewport& viewport, const Picker& picker, const ModelTree& modelTree)
    :mViewport(viewport),
    mPicker(picker),
     mModelTree(modelTree)
    
{
    
}
    
void Snap::setStartViewport(const glm::vec2& startViewport, bool assignScene)
{
    mStartViewport = startViewport;
    if (assignScene) {
        mStartScene = mPicker.PickSceneCoordinates(startViewport);
    }
}
    
void Snap::setEndViewport(const glm::vec2& endViewport, bool assignScene)
{
    mEndViewport = endViewport;
    if (assignScene) {
        mEndScene = mPicker.PickSceneCoordinates(endViewport);
    }
}
    
void Snap::setStartScene(const glm::vec3& startScene, bool assignViewport)
{
    mStartScene = startScene;
    if (assignViewport) {
        mStartViewport = mViewport.CoordsAt(mStartScene);
    }
}
    
void Snap::setEndScene(const glm::vec3& endScene, bool assignViewport)
{
    mEndScene = endScene;
    if (assignViewport) {
        mEndViewport = mViewport.CoordsAt(mEndScene);
    }
}

    
}
