

#import <XCTest/XCTest.h>

#include <Graph/PointNode.h>
#include <Processing/ModelEditor.h>

using namespace ftr;

@interface TestPointNode : XCTestCase
{
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    PointNode* v5;
    PointNode* v6;
}

@end

@implementation TestPointNode

- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    v5 = new PointNode(glm::vec3(1.0f, -1.0f, 0.0f));
    v6 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";
    v6->mName = "6";
}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    [super tearDown];
}


- (void)testInvalidate
{
    ModelEditor editor;
    editor.DebugCreateCube();
    BodyNode* activeBody = editor.activeBody();
    
    std::vector<Node*> pointNodes;
    std::vector<Node*> lineNodes;
    std::vector<Node*> faceNodes;
    activeBody->SubnodesWithType(Node::kPoint, pointNodes);
    activeBody->SubnodesWithType(Node::kLine, lineNodes);
    activeBody->SubnodesWithType(Node::kFace, faceNodes);
    
    PointNode* pointNode = reinterpret_cast<PointNode*>(pointNodes[0]);
    
    pointNode->Invalidate(true);
    
    XCTAssertEqual(pointNodes.size(), 8);
    XCTAssertEqual(lineNodes.size(), 12);
    XCTAssertEqual(faceNodes.size(), 6);
    
    int invalidPointsCount = 0;
    for (auto& point : pointNodes) invalidPointsCount += point->invalid();
    XCTAssertEqual(invalidPointsCount, 1);
    
    int invalidLinesCount = 0;
    for (auto& line : lineNodes) invalidLinesCount += line->invalid();
    XCTAssertEqual(invalidLinesCount, 3);
    
    int invalidFacesCount = 0;
    for (auto& face : faceNodes) invalidFacesCount += face->invalid();
    XCTAssertEqual(invalidFacesCount, 3);
}




@end
