
#include <Query/Query.h>
#include <Processing/ModelTree.h>
#include <Graph/PointNode.h>
#include <Graph/FaceNode.h>

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
        point->name = node->vertex().mName;
        point->sceneCoords = node->Origin();
        points.push_back(point);
    }
}
    
void Query::Faces(std::vector<Face*>& faces) const
{
    std::vector<FaceNode*> faceNodes;
    mModelTree.FaceNodes(faceNodes);
    
    for (FaceNode* node : faceNodes) {
        Face* face = new Face();
        face->name = node->Description();
        faces.push_back(face);
    }
}
 
    
}