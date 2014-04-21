
#pragma once

#include <Graph/ModelFactory.h>
#include <Graph/GroupNode.h>
#include <Graph/BodyNode.h>
#include <Processing/ModelTree.h>

namespace ftr {

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
    //
    // Creating
    //
    PointNode*      CreatePoint(glm::vec3 origin);
    LineNode*       CreateLine(PointNode* startPoint, PointNode* endPoint);
    BodyNode*       CreateBody();
    GroupNode*      CreateGroup();
private:
    
    class ModelFactory* mModelFactory;
    class ModelTree*    mModelTree;
    GroupNode*          mActiveGroup;
    BodyNode*           mActiveBody;
};
    
}
