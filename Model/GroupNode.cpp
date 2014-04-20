

#include <Model/BodyNode.h>
#include <Model/GroupNode.h>

namespace ftr {
    
void GroupNode::AddBody(BodyNode* bodyNode)
{
    AddNode(bodyNode);
}
    
void GroupNode::Render(Layer& layer)
{
    Node::Render(layer);
}
    
}