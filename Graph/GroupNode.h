#pragma once

#include <Graph/Node.h>

namespace ftr {

class FaceNode;
class BodyNode;
    
class GroupNode : public Node
{
public:
    
    virtual enum Type Type() const { return kGroup; }
    void AddBody(BodyNode* bodyNode);

    virtual void Render(Layer& layer);
    
private:
};

}