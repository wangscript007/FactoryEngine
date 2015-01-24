

#import <XCTest/XCTest.h>
#import <Graph/FaceNode.h>
#import <Geometry/Vector.h>
#include <Geometry/Constants.h>

using namespace ftr;


@interface TestFaceNode : XCTestCase {
}

@end

@implementation TestFaceNode



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
    
    FaceNode* faceNode = reinterpret_cast<FaceNode*>(faceNodes[0]);
    
    faceNode->Invalidate(true);
    
    XCTAssertEqual(pointNodes.size(), 8);
    XCTAssertEqual(lineNodes.size(), 12);
    XCTAssertEqual(faceNodes.size(), 6);
    
    int invalidPointsCount = 0;
    for (auto& point : pointNodes) invalidPointsCount += point->invalid();
    XCTAssertEqual(invalidPointsCount, 4);
    
    int invalidLinesCount = 0;
    for (auto& line : lineNodes) invalidLinesCount += line->invalid();
    XCTAssertEqual(invalidLinesCount, 8);
    
    int invalidFacesCount = 0;
    for (auto& face : faceNodes) invalidFacesCount += face->invalid();
    XCTAssertEqual(invalidFacesCount, 5);
}




@end
