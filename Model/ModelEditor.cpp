
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
        fDistance = (sSphere.mCenter - (*i)->mOrigin).Length();
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

FaceNode* ModelEditor::CreateRectangle(const Vec3& origin, const Vec3& size) const
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


FaceNode* ModelEditor::CreateFace(Vec3 origin, FaceNode::FaceType eType)
{
    assert(mSelectedNode);
    FaceNode* pFace = mModelFactory->CreateFace(Vec3(origin.mX, 0.01, origin.mZ),
                                Vec3(0.0f, 0.0f, 0.0f),
                                eType);
    mSelectedNode->AddNode(pFace);
    return pFace;
}

PointNode* ModelEditor::CreatePoint(Vec3 origin)
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

