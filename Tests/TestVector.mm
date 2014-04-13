

#import <XCTest/XCTest.h>
#import <Geometry/Vector.h>

using namespace ftr;

@interface TestVector : XCTestCase

@end

@implementation TestVector

- (void)setUp
{
    [super setUp];
    // Put setup code here; it will be run once, before the first test case.
}

- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

- (void)testIsCWInXYPlane
{
    glm::vec3 p1 = glm::vec3(0.0);
    glm::vec3 p2 = glm::vec3(1.0f, 1.0f, 0.0f);
    glm::vec3 p3 = glm::vec3(0.0f, 2.0f, 0.0f);
    glm::vec3 p4 = glm::vec3(2.0f, 0.0f, 0.0f);
    
    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p2;
    glm::vec3 v3 = p4 - p2;
    
    XCTAssertFalse(Vector::IsCWOrder(v1, v2));
    XCTAssert(Vector::IsParallel(v1, v3));
    XCTAssertFalse(Vector::IsCWOrder(v1, v3));
}

- (void)testIsParallel
{
    XCTAssertTrue(Vector::IsParallel(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    XCTAssertTrue(Vector::IsParallel(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    XCTAssertTrue(Vector::IsParallel(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
    
    XCTAssertFalse(Vector::IsParallel(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    XCTAssertFalse(Vector::IsParallel(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
    XCTAssertFalse(Vector::IsParallel(glm::vec3(0.8f, 1.0f, 0.0f), glm::vec3(0.7f, -.0f, 0.0f)));
}

- (void)testIsCWInXZPlane
{
    glm::vec3 p1 = glm::vec3(0.0);
    glm::vec3 p2 = glm::vec3(1.0f, 0.0f, 1.0f);
    glm::vec3 p3 = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 p4 = glm::vec3(2.0f, 0.0f, 0.0f);
    
    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p2;
    glm::vec3 v3 = p4 - p2;
    
    XCTAssert(Vector::IsParallel(v1, v2));
    XCTAssertFalse(Vector::IsCWOrder(v1, v2));
    XCTAssertFalse(Vector::IsCWOrder(v1, v3));
}

- (void)testIsCWInYZPlane
{
    glm::vec3 p1 = glm::vec3(0.0);
    glm::vec3 p2 = glm::vec3(0.0f, 1.0f, 1.0f);
    glm::vec3 p3 = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 p4 = glm::vec3(0.0f, 2.0f, 0.0f);
    
    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p2;
    glm::vec3 v3 = p4 - p2;
    
    XCTAssertFalse(Vector::IsCWOrder(v1, v2));
    XCTAssertFalse(Vector::IsCWOrder(v1, v3));
}

- (void)testCWAngle
{
    glm::vec3 v1 = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 v2 = glm::vec3(1.0f, 1.0f, 0.0f);
    glm::vec3 v3 = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 v4 = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 v5 = glm::vec3(0.0f, 0.0f, 0.0f);
    
    glm::vec3 e53 = glm::normalize(v3 - v5);
    glm::vec3 e32 = glm::normalize(v2 - v3);
    glm::vec3 e31 = glm::normalize(v1 - v3);
    
    XCTAssertEqualWithAccuracy(Vector::CCWAngle(e53, e31), 135.0f, 0.01f);
    XCTAssertEqualWithAccuracy(Vector::CCWAngle(e53, e32), 90.0f, 0.01f);
}

bool IsEqualVec(const glm::vec3& vec1, const glm::vec3& vec2)
{
    glm::detail::tvec3<bool> equal = glm::epsilonEqual(vec1, vec2, 0.0001f);
    return equal.x && equal.y && equal.z;
}

- (void)testXYZClosestAxis
{
    glm::vec3 x = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 y = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 z = glm::vec3(0.0f, 0.0f, 1.0f);
    
    XCTAssertTrue(IsEqualVec(x, Vector::XYZClosestAxis(x)));
    XCTAssertTrue(IsEqualVec(x, Vector::XYZClosestAxis(-x)));
    XCTAssertTrue(IsEqualVec(-y, Vector::XYZClosestAxis(y)));
    XCTAssertTrue(IsEqualVec(-y, Vector::XYZClosestAxis(-y)));
    XCTAssertTrue(IsEqualVec(z, Vector::XYZClosestAxis(z)));
    XCTAssertTrue(IsEqualVec(z, Vector::XYZClosestAxis(-z)));
    
    glm::vec3 x2 = glm::vec3(1.0f, 0.5f, 0.0f);
    glm::vec3 y2 = glm::vec3(0.9f, 1.0f, 0.0f);
    glm::vec3 z2 = glm::vec3(0.0f, 0.1f, 1.0f);
    
    XCTAssertTrue(IsEqualVec(x, Vector::XYZClosestAxis(x2)));
    XCTAssertTrue(IsEqualVec(x, Vector::XYZClosestAxis(-x2)));
    XCTAssertTrue(IsEqualVec(-y, Vector::XYZClosestAxis(y2)));
    XCTAssertTrue(IsEqualVec(-y, Vector::XYZClosestAxis(-y2)));
    XCTAssertTrue(IsEqualVec(z, Vector::XYZClosestAxis(z2)));
    XCTAssertTrue(IsEqualVec(z, Vector::XYZClosestAxis(-z2)));
    
    
}




@end
