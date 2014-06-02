
#include <Processing/ModelEditor.h>
#include <Processing/FaceExtruder.h>
#include <Processing/ColorPickingMapper.h>
#include <Scene/Picker.h>

namespace ftr {

ModelEditor::ModelEditor()
    :mModelFactory(NULL),
    mModelTree(NULL),
    mActiveGroup(NULL),
    mActiveBody(NULL),
    mDebugFacesCreated(0)
    
{
    mModelTree = new class ModelTree();
    mModelFactory = new class ModelFactory(*mModelTree);
    mActiveGroup = CreateGroup();
    mActiveBody = CreateBody();
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
    assert(mActiveBody);
    LineNode* line = mModelFactory->CreateLine(startPoint, endPoint);
    PointNode::ConnectionResult result = startPoint->ConnectTo(endPoint);
    mDebugFacesCreated += result.count();
    mActiveBody->AddNode(line);
    if (result.faces[0]) {
        mActiveBody->AddNode(result.faces[0]);
        static bool extruded = false;
        if (!extruded && false) {
            extruded = true;
            FaceExtruder extruder(*this);
            extruder.Extrude(*result.faces[0]);
        }
    }
    if (result.faces[1]) {
        mActiveBody->AddNode(result.faces[1]);
    }
    return line;
}
    
BodyNode* ModelEditor::CreateBody()
{
    BodyNode* body = mModelFactory->CreateBody();
    mActiveGroup->AddBody(body);
    return body;
}
    
GroupNode* ModelEditor::CreateGroup()
{
    GroupNode* group = mModelFactory->CreateGroup();
    mModelTree->AddGroup(group);
    return group;
}
    
#pragma mark Debug
    
void ModelEditor::DebugCreateCube()
{
    return;
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

