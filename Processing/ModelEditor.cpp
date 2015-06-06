
#include <Processing/ModelEditor.h>
#include <Processing/FaceExtruder.h>
#include <Processing/ColorPickingMapper.h>
#include <Processing/FaceTraversal.h>
#include <Scene/Picker.h>
#include <Graph/Node.h>
#include <Graph/ModelFactory.h>
#include <Graph/GroupNode.h>
#include <Graph/BodyNode.h>
#include <Graph/LineNode.h>
#include <Graph/Vertex.h>
#include <Graph/Edge.h>



namespace ftr {

ModelEditor::ModelEditor()
    :mModelFactory(NULL),
    mModelTree(NULL),
    mActiveGroup(NULL),
    mActiveBody(NULL),
    mSelectedNode(NULL)
    
{
    mModelTree = new class ModelTree();
    mModelFactory = new class ModelFactory(*mModelTree);
    CreateGroup();
    CreateBody();
}

ModelEditor::~ModelEditor()
{
    FT_DELETE(mModelFactory);
    FT_DELETE(mModelTree);
    FT_DELETE(mActiveGroup);
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
        fDistance = glm::length(sSphere.mCenter - (*i)->Origin());
        if (fDistance < sSphere.mRadius) {
            if (fDistance < fNearestPointDistance) {
                pNearestPoint = *i;
                fNearestPointDistance = fDistance;
            }
        }
    }
    return pNearestPoint;
}

#pragma mark Creating
    
PointNode* ModelEditor::CreatePoint(glm::vec3 origin)
{
    assert(mActiveBody);
    PointNode* pPoint = mModelFactory->CreatePoint(origin);
    mActiveBody->AddNode(pPoint);
    mModelTree->AddNode(pPoint);
    return pPoint;
}

LineNode* ModelEditor::CreateLine(PointNode* startPoint, PointNode* endPoint)
{
    if (startPoint->IsConnectedTo(*endPoint)) return NULL;
    
    assert(mActiveBody);
    LineNode* line = mModelFactory->CreateLine(startPoint, endPoint);
    mActiveBody->AddNode(line);
    
    Vertex& vertexA = startPoint->vertex();
    Vertex& vertexB = endPoint->vertex();
    Edge* edge = vertexA.ConnectTo(vertexB);
    edge->mLineNode = line;
    line->mEdge = edge;
    
    FaceTraversal traversal(vertexA);
    FaceTraversal::Result result;
    do {
        traversal.Find(result);
        if (result.Found()) {
            CreateFace(result.mVertexes);
        }
    } while (result.Found());
    
    return line;
}
    
FaceNode* ModelEditor::CreateFace(std::vector<PointNode*> pointNodes)
{
    FaceNode* face = mModelFactory->CreateFace(pointNodes);
    mActiveBody->AddFaceNode(face);
    return face;
}
    
FaceNode* ModelEditor::CreateFace(const std::vector<Vertex*>& vertexes)
{
    FaceNode* face = mModelFactory->CreateFace(vertexes);
    mActiveBody->AddFaceNode(face);
    return face;
}

    
BodyNode* ModelEditor::CreateBody()
{
    mActiveBody = mModelFactory->CreateBody();
    mActiveGroup->AddBody(mActiveBody);
    return mActiveBody;
}
    
GroupNode* ModelEditor::CreateGroup()
{
    mActiveGroup = mModelFactory->CreateGroup();
    mModelTree->AddGroup(mActiveGroup);
    return mActiveGroup;
}
    
#pragma mark Editing
    
void ModelEditor::Select(Node* node)
{
    if (node && node != mSelectedNode) {
        if (mSelectedNode) {
            mSelectedNode->setSelected(false);
        }
        mSelectedNode = node;
        mSelectedNode->setSelected(true);
    }
}
    
Node* ModelEditor::Select(const glm::vec2& point)
{
    Node* node = mPicker->PickNode(point);
    Select(node);
    return mSelectedNode;
}
    
Node* ModelEditor::SelectNodeWithID(int nodeID)
{
    Node* node = mPicker->PickNodeWithID(nodeID);
    Select(node);
    return mSelectedNode;
}

    
void ModelEditor::Move(const glm::vec3 &offset)
{
    mSelectedNode->Transform(glm::translate(offset));
    mSelectedNode->Invalidate(true);
    UpdateNode(mSelectedNode);
}

    
#pragma mark Debug
    
void ModelEditor::DebugCreateCube()
{
//    return;
    Box box(glm::vec3(0.0, 3.0, 0.0), glm::vec3(2.0, 2.0, 3.0));
    const glm::vec3 c = box.mCenter;
    const glm::vec3 h = box.mHalfDimension;
    
    glm::vec3 p[] = {
        glm::vec3(c.x - h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y - h.y, c.z - h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z - h.z)
    };
    
    static const GLubyte indices[] = {
        0, 1,   1, 2,   2, 3,   3, 0,
        4, 5,   5, 6,   6, 7,   7, 4,
        0, 4,   1, 5,   2, 6,   3, 7
    };
    
    PointNode* nodes[8];
    for(int i = 0; i < 8; ++i) {
        nodes[i] = CreatePoint(p[i]);
    }
    
    for (int i = 0; i < 12; i++) {
        CreateLine(nodes[indices[i*2]], nodes[indices[i*2+1]]);
    }
}

    
    
}

