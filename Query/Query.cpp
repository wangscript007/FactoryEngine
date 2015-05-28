
#include <Query/Query.h>
#include <Processing/ModelTree.h>
#include <Graph/PointNode.h>

namespace ftr {
    
Query::Query(ModelTree& modelTree)
    :mModelTree(modelTree)
{
    
}
    
void Query::Points(std::vector<Query::Point*>& points) const
{
    std::vector<PointNode*> pointNodes;
    mModelTree.PointNodes(pointNodes);
    for (PointNode* node : pointNodes) {
        Point* point = new Point();
        point->name = node->mName;
        point->sceneCoords = node->Origin();
        points.push_back(point);
    }
}
 
    
}