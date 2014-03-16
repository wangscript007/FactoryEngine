
#import <XCTest/XCTest.h>
#import <Math/Plane.h>


using namespace ftr;

@interface TestPlane : XCTestCase
{
    Plane plane;
    glm::vec3 p1, p2, p3, p4, p5;
}

@end

@implementation TestPlane

- (void)setUp
{
    [super setUp];
    p1 = glm::vec3(0.0f, 1.0f, 0.0f);
    p2 = glm::vec3(1.0f, 1.0f, 0.0f);
    p3 = glm::vec3(1.0f, 0.0f, 0.0f);
    p4 = glm::vec3(0.0f, -1.0f, 0.0f);
    p5 = glm::vec3(0.0f, -1.0f, 1.0f);
    plane = Plane(p1, p2, p3);
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testContains
{
    XCTAssert(plane.Contains(p4));
    XCTAssert(!plane.Contains(p5));
}

@end
