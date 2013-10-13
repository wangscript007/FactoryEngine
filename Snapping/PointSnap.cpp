
#include <Snapping/PointSnap.h>
#include <Model/PointNode.h>

namespace ftr {
    
glm::vec3 PointSnap::Snapped() const
{
    PointNode* pointNode = NearestPointToCenterInSphere(Sphere(mStartScene, 0.5f));
    if (pointNode) {
        return pointNode->mOrigin;
    } else {
        return mStartScene;
    }
}
    
PointNode* PointSnap::NearestPointToCenterInSphere(const Sphere& sphere) const
{
    std::vector<PointNode*> pointsVector;
    Box box = sphere.Box();
    mModelTree.PointNodesInBox(box, pointsVector);
    PointNode* nearestPoint = NULL;
    float nearestPointDistance = MAXFLOAT;
    float distance;
    for(auto i = pointsVector.begin(); i != pointsVector.end(); ++i) {
        distance = glm::length(sphere.mCenter - (*i)->mOrigin);
        if (distance < sphere.mRadius) {
            if (distance < nearestPointDistance) {
                nearestPoint = *i;
                nearestPointDistance = distance;
            }
        }
    }
    return nearestPoint;
}

    
}

