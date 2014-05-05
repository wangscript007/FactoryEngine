
#pragma once

#include <Graph/Node.h>
#include <Graph/ModelFactory.h>
#include <Graph/GroupNode.h>
#include <Graph/BodyNode.h>
#include <Processing/ModelTree.h>

namespace ftr {
    
class ColorPickingMapper;
class Picker;

class ModelEditor
{
public:
                    ModelEditor();
                    ~ModelEditor();
    
    ModelFactory*   ModelFactory() const { return mModelFactory; }
    ModelTree*      ModelTree() const { return  mModelTree; }
    PointNode*      NearestPointToCenterInSphere(const Sphere& sSphere) const;
    void            UpdateNode(Node* pNode) { mModelTree->UpdateNode(pNode); }
    void            RemoveNode(Node* pNode) { mModelTree->RemoveNode(pNode); }
    
    GroupNode*      activeGroup() const { return mActiveGroup; }
    BodyNode*       activeBody() const { return mActiveBody; }
    
    unsigned long   Size() { return mModelTree->Size(); }

    
    PointNode*      CreatePoint(glm::vec3 origin);
    LineNode*       CreateLine(PointNode* startPoint, PointNode* endPoint);
    BodyNode*       CreateBody();
    GroupNode*      CreateGroup();
    
    Picker*         picker() const { return mPicker; }
    void            setPicker(Picker* picker) { mPicker = picker; }
    
    void            DebugCreateCube();
private:
    
    class ModelFactory* mModelFactory;
    class ModelTree*    mModelTree;
    GroupNode*          mActiveGroup;
    BodyNode*           mActiveBody;
    Picker*             mPicker;
};
    
}
