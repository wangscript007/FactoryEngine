
#pragma once

namespace ftr {
    
class FaceNode;
class PointNode;

class FaceTraversal
{
public:
    static FaceNode* TryToCreateFaceByConnectingNode(PointNode& pointNode);
    
private:
};
    
}

