
#pragma once

#include <Model/ModelTree.h>
#include <Model/FaceNode.h>

namespace ftr {

class FaceTraversal
{
public:
    FaceTraversal(const ModelTree& modelTree);
    virtual ~FaceTraversal() {}
    
    FaceNode* TraverseNode(const PointNode& pointNode) const;
    
private:
    const ModelTree& mModelTree;
};
    
}

