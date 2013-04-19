#pragma once

#include <Model/Node.h>

namespace ftr {

class ModelManager;

class MoveInteraction : public Node
{
public:
    MoveInteraction(ModelManager& modelManager);
    virtual ~MoveInteraction() {}
    void Render();
    
    void setStart(Vec3 start);
    void setEnd(Vec3 end);
    
private:
    Vec3 mStart;
    Vec3 mEnd;
    Node* mNode;
    ModelManager& mModelManager;
    bool mActive;
};
    
}

