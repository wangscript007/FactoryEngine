
#include <Graph/ModelFactory.h>
#include <Graph/PointNode.h>
#include <Graph/LineNode.h>
#include <Graph/FaceNode.h>
#include <Graph/GroupNode.h>
#include <Graph/BodyNode.h>
#include <Graph/Vertex.h>

namespace ftr {

ModelFactory::ModelFactory(ModelTree& ModelTree)
    :mModelTree(ModelTree)
{
    
}

PointNode* ModelFactory::CreatePoint(glm::vec3 origin) const
{
    static int index = 0;
    PointNode* pPoint = new PointNode();
    pPoint->SetOrigin(origin);
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
    
FaceNode* ModelFactory::CreateFace(std::vector<PointNode*> pointNodes) const
{
    FaceNode* face = new FaceNode(pointNodes);
    return face;
}
    
FaceNode* ModelFactory::CreateFace(const std::vector<Vertex*>& vertexes)
{
    FaceNode* face = new FaceNode(vertexes);
    return face;
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