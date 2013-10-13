
#include <Snapping/Snap.h>

namespace ftr {
    
Snap::Snap(const Viewport& viewport, const ModelTree& modelTree)
    :mViewport(viewport),
     mModelTree(modelTree)
{
    
}
    
void Snap::setStartViewport(const glm::vec2& startViewport, bool assignScene)
{
    mStartViewport = startViewport;
    if (assignScene) {
        mStartScene = mViewport.SceneCoordsAt(startViewport);
    }
}
    
void Snap::setEndViewport(const glm::vec2& endViewport, bool assignScene)
{
    mEndViewport = endViewport;
    if (assignScene) {
        mEndScene = mViewport.SceneCoordsAt(endViewport);
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
