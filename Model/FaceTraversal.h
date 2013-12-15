
#pragma once

namespace ftr {
    
class FaceNode;
class PointNode;

class FaceTraversal
{
public:
    FaceNode* CreateFaceByConnectingNode(PointNode& pointNode) const;
    
private:
};
    
}

