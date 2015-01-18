
#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#import <Graph/Vertex.h>
#import <Graph/Edge.h>
#import <Processing/FaceTraversal.h>

using namespace ftr;

@interface TestFaceTraversal : XCTestCase

@end

@implementation TestFaceTraversal

- (void)testTriangle
{
    Vertex vertex[3];
    vertex[0].mOrigin = glm::vec3(0);
    vertex[1].mOrigin = glm::vec3(0, 1, 0);
    vertex[2].mOrigin = glm::vec3(1, 0, 0);
    vertex[2].mOrigin = glm::vec3(1, 0, 0);
    
    vertex[0].ConnectTo(vertex[1]);
    vertex[1].ConnectTo(vertex[2]);
    vertex[2].ConnectTo(vertex[0]);
    
    for(int i = 0; i < 3; i++) {
        
        std::stringstream ss;
        ss << i;
        vertex[i].mName = ss.str();
    }
    
    FaceTraversal traversal(vertex[0]);
    FaceTraversal::Result result;
    traversal.Find(result);
    XCTAssert(result.Found());
}

- (void)testTwoTriangles
{
    Vertex vertex[4];
    vertex[0].mOrigin = glm::vec3(0);
    vertex[1].mOrigin = glm::vec3(0, 1, 0);
    vertex[2].mOrigin = glm::vec3(1, 0, 0);
    vertex[3].mOrigin = glm::vec3(1, 1, 0);
    
    vertex[0].ConnectTo(vertex[1]);
    vertex[1].ConnectTo(vertex[2]);
    vertex[2].ConnectTo(vertex[0]);
    vertex[3].ConnectTo(vertex[1]);
    vertex[3].ConnectTo(vertex[2]);
    
    for(int i = 0; i < 4; i++) {
        
        std::stringstream ss;
        ss << i;
        vertex[i].mName = ss.str();
    }
    
    FaceTraversal traversal(vertex[0]);
    FaceTraversal::Result result;
    traversal.Find(result);
    XCTAssert(result.Found());
}


@end
