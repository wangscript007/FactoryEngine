
#include <Model/ModelEditor.h>

namespace ftr {

ModelEditor::ModelEditor()
    :mSelectedNode(NULL)
{
    mModelTree = new class ModelTree();
    mModelFactory = new class ModelFactory(*mModelTree);
    mRootGroup = new Group();
    mModelTree->setRootNode(mRootGroup);
    Select(mRootGroup);
    
}

ModelEditor::~ModelEditor()
{
    FT_DELETE(mModelFactory);
    FT_DELETE(mModelTree);
    FT_DELETE(mRootGroup);
}

#pragma mark - Instance

PointNode* ModelEditor::NearestPointToCenterInSphere(const Sphere& sSphere) const
{
    std::vector<PointNode*> cPointsVector;
    Box sBox = sSphere.Box();
    mModelTree->PointNodesInBox(sBox, cPointsVector);
    PointNode* pNearestPoint = NULL;
    float fNearestPointDistance = MAXFLOAT;
    float fDistance;
    for(auto i = cPointsVector.begin(); i != cPointsVector.end(); ++i) {
        fDistance = glm::length(sSphere.mCenter - (*i)->mOrigin);
        if (fDistance < sSphere.mRadius) {
            if (fDistance < fNearestPointDistance) {
                pNearestPoint = *i;
                fNearestPointDistance = fDistance;
            }
        }
    }
    return pNearestPoint;
}

void ModelEditor::Select(Node* pNode)
{
    mSelectedNode = pNode;
}


PointNode* ModelEditor::CreatePoint(glm::vec3 origin)
{
    assert(mSelectedNode);
    PointNode* pPoint = mModelFactory->CreatePoint(origin);
    mSelectedNode->AddNode(pPoint);
    mModelTree->AddNode(pPoint);
    return pPoint;
}

LineNode* ModelEditor::CreateLine(PointNode* startPoint, PointNode* endPoint)
{
    assert(mSelectedNode);
    LineNode* line = mModelFactory->CreateLine(startPoint, endPoint);
    mSelectedNode->AddNode(line);
    mSelectedNode = line;
    
    return line;
    
}
    
}

