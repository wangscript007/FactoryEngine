
#import <XCTest/XCTest.h>
#import <Math/Triangle.h>


using namespace ftr;

@interface TestPlane : XCTestCase
{
    Triangle Triangle;
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
    Triangle = Triangle(p1, p2, p3);
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testContains
{
    XCTAssert(Triangle.Contains(p1));
    XCTAssert(Triangle.Contains(p2));
    XCTAssert(Triangle.Contains(p3));
    XCTAssert(Triangle.Contains(p4));
    XCTAssert(!Triangle.Contains(p5));
}

@end
