
namespace ftr {
    
class Edge;
class PointNode;
    
class FaceReversal
{
public:
    void ReverseIslandWithBridgeEdge(Edge& edge);
    
private:
    void Reverse(PointNode& pointNode);
    
    PointNode* mStartPoint;
    PointNode* mStopPoint;

    
};

}