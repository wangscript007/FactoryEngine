
#include <Graph/ModelFactory.h>
#include <Processing/FaceTraversal.h>

namespace ftr {

ModelFactory::ModelFactory(ModelTree& ModelTree)
    :mModelTree(ModelTree)
{
    
}

PointNode* ModelFactory::CreatePoint(glm::vec3 origin) const
{
    static int index = 0;
    PointNode* pPoint = new PointNode();
    pPoint->mOrigin = origin;
    index++;
    std::ostringstream convert;
    convert << index << "n";
    pPoint->mName = convert.str();
    return pPoint;
}

LineNode* ModelFactory::CreateLine(PointNode* startPoint, PointNode* endPoint) const
{
    LineNode* line = new LineNode(startPoint, endPoint);
    return line;
}
    
BodyNode* ModelFactory::CreateBody()
{
    BodyNode* body = new BodyNode();
    return body;
}
    
GroupNode* ModelFactory::CreateGroup()
{
    GroupNode* group = new GroupNode();
    return group;
}

        
}