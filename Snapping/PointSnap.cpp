
#include <Snapping/PointSnap.h>
#include <Model/PointNode.h>

namespace ftr {
    
glm::vec3 PointSnap::Snapped() const
{
    PointNode* point = SnappedPoint();
    return point ? point->mOrigin : mStartScene;
}
    
PointNode* PointSnap::SnappedPoint() const
{
    const Segment& segment = mViewport.RayAtPoint(mStartViewport);
    const Cylinder& cylinder = Cylinder(segment, 0.5f);
    PointNode* pointNode = NearestPointToAxisInCylinder(cylinder);
    if (pointNode) {
        return pointNode;
    } else {
        return NULL;
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
    
PointNode* PointSnap::NearestPointToAxisInCylinder(const Cylinder& cylinder) const
{
    std::vector<PointNode*> pointsVector;
    mModelTree.PointNodesInCylinder(cylinder, pointsVector);
    PointNode* nearestPoint = NULL;
    float nearestPointDistance = MAXFLOAT;
    float distance;
    for(auto i = pointsVector.begin(); i != pointsVector.end(); ++i) {
        distance = cylinder.mAxis.DistanceFromPoint((*i)->mOrigin);
        if (distance < cylinder.mRadius) {
            if (distance < nearestPointDistance) {
                nearestPoint = *i;
                nearestPointDistance = distance;
            }
        }
    }
    return nearestPoint;
}


    
}

