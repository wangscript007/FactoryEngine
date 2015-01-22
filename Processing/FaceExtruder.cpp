
#include <Processing/FaceExtruder.h>
#include <Processing/ModelEditor.h>
#include <Graph/FaceNode.h>
#include <Graph/PointNode.h>

const float kExtrudeMinOffset = 2.0f;

namespace ftr {
    
FaceExtruder::FaceExtruder(ModelEditor& modelEditor)
    :mModelEditor(modelEditor)
{
    
}
    
FaceExtruder::~FaceExtruder()
{
    
}
    

void FaceExtruder::Extrude(FaceNode &faceNode)
{
    mFaceNode = &faceNode;
    glm::vec3 offsetVec = mFaceNode->SurfaceNormal()*kExtrudeMinOffset;
    std::vector<PointNode*> pointNodes;
    mFaceNode->GetPointNodes(pointNodes);
    
    PointNode* startPointNode = NULL;
    PointNode* lastPointNode = NULL;
    
    for (int i = 0; i < pointNodes.size(); ++i)
    {
        PointNode* twinPointNode = mModelEditor.CreatePoint(pointNodes[i]->Origin() + offsetVec);
        mModelEditor.CreateLine(twinPointNode, pointNodes[i]);
        if (i > 0) {
            mModelEditor.CreateLine(lastPointNode, twinPointNode);
        } else {
            startPointNode = twinPointNode;
        }
        lastPointNode = twinPointNode;
    }
    mModelEditor.CreateLine(lastPointNode, startPointNode);
}


    


    
}