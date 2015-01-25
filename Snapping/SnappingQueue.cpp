
#include <Snapping/SnappingQueue.h>
#include <Snapping/PointSnap.h>
#include <Snapping/AxisSnap.h>

namespace ftr {
    
SnappingQueue::SnappingQueue(const Viewport& viewport, const Picker& picker, const ModelTree& modelTree)
    : Snap::Snap(viewport, picker, modelTree)
{
    mSnapsVector.push_back(new PointSnap(viewport, picker, modelTree));
    mSnapsVector.push_back(new AxisSnap(viewport, picker, modelTree));
}
    
glm::vec3 SnappingQueue::Snapped() const
{
    PointSnap* pointSnap = reinterpret_cast<PointSnap*>(mSnapsVector[0]);
    AxisSnap * axisSnap = reinterpret_cast<AxisSnap*>(mSnapsVector[1]);
    
    glm::vec3 snapped;
    pointSnap->setStartViewport(mStartViewport);
    pointSnap->setStartScene(mStartScene);
    snapped = pointSnap->Snapped();

    if (mStartScene != mEndScene) {
        axisSnap->setStartScene(snapped, true);
        axisSnap->setEndScene(mEndScene);
        axisSnap->setEndViewport(mEndViewport);
        snapped = axisSnap->Snapped();
        
        pointSnap->setStartScene(snapped, true);

        snapped = pointSnap->Snapped();
    }
    
    return snapped;
    
    
    
    /*
    glm::vec3 snapped = mEndScene;
    for (auto i = mSnapsVector.begin(); i != mSnapsVector.end(); ++i)
    {
        Snap* snap = (*i);
        
        snap->setStartScene(mStartScene);
        snap->setEndScene(snapped);
        
        snap->setStartViewport(mStartViewport);
        snap->setEndViewport(mEndViewport);
        snapped = snap->Snapped();
    }
    return snapped;
    */
}


}
