
#include <Model/ModelEditor.h>

namespace ftr {

ModelEditor::ModelEditor()
    :mSelectedNode(NULL)
{
    mModelTree = new class ModelTree();
    mModelFactory = new class ModelFactory(*mModelTree);
    mRootGroup = new Group();
    mModelTree->setRootNode(mRootGroup);
    
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

FaceNode* ModelEditor::CreateRectangle(const glm::vec3& origin, const glm::vec3& size) const
{
    assert(mSelectedNode);
    FaceNode* pFace = mModelFactory->CreateRectangle(origin, size);
    mSelectedNode->AddNode(pFace);
    const FaceNode::TPointsVector& pointsVector = pFace->PointNodesVector();
    for(auto i = pointsVector.begin(); i != pointsVector.end(); ++i) {
        mModelTree->AddNode(*i);
    }
    return pFace;
}


FaceNode* ModelEditor::CreateFace(glm::vec3 origin, FaceNode::FaceType eType)
{
    assert(mSelectedNode);
    FaceNode* pFace = mModelFactory->CreateFace(glm::vec3(origin.x, 0.01, origin.z),
                                                glm::vec3(0.0f, 0.0f, 0.0f),
                                                eType);
    mSelectedNode->AddNode(pFace);
    return pFace;
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

