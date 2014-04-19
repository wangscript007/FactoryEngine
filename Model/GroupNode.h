#pragma once

#include <Model/Node.h>

namespace ftr {

class FaceNode;
class BodyNode;
    
class GroupNode : public Node
{
public:
    enum Level {
        kFace,
        kBody,
        kGroup
    };
    
    void AddBody(BodyNode* bodyNode);

    
private:
    Level mLevel;
};

}