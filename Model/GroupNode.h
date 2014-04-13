#pragma once

#include <Model/Node.h>

namespace ftr {

class FaceNode;
    
class GroupNode : public Node
{
public:
    enum Level {
        kFace,
        kBody,
        kGroup
    };
    
    std::vector<FaceNode*> mFaces;
    
private:
    Level mLevel;
};

}