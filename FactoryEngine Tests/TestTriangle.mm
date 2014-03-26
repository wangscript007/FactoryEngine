
#import <XCTest/XCTest.h>
#import <Geometry/Triangle.h>


using namespace ftr;

@interface TestPlane : XCTestCase
{
    Triangle triangle;
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
    triangle = Triangle(p1, p2, p3);
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testContains
{
    XCTAssert(triangle.PlaneContains(p1));
    XCTAssert(triangle.PlaneContains(p2));
    XCTAssert(triangle.PlaneContains(p3));
    XCTAssert(triangle.PlaneContains(p4));
    XCTAssert(!triangle.PlaneContains(p5));
}

@end
