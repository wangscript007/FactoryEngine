#pragma once

#include <Model/Node.h>

namespace ftr {

class FaceNode;
class BodyNode;
    
class GroupNode : public Node
{
public:
    
    virtual NodeType Type() const { return kGroup; }
    void AddBody(BodyNode* bodyNode);

    virtual void            Render(Layer& layer);
    
private:
};

}