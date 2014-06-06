
#include <Processing/FaceReversal.h>
#include <Graph/Edge.h>

namespace ftr {
    
void FaceReversal::ReverseIslandWithBridgeEdge(Edge& edge)
{
    mStartPoint = edge.originNode();
    mStopPoint  = edge.targetNode();
}
    
void FaceReversal::Reverse(PointNode& pointNode)
{
    
}

}