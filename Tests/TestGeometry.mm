
#import <XCTest/XCTest.h>
#import <Geometry/Geometry.h>
#import <Geometry/GeometryPrimitives.h>
#import <Main/Constants.h>


using namespace ftr;

@interface TestGeometry : XCTestCase {
}

@end

@implementation TestGeometry

- (void)setUp
{
    [super setUp];
    
}

- (void)tearDown
{

    [super tearDown];
}

- (void)testCenter
{
    Box mBox(glm::vec3(0.0, 0.0, 0.0), glm::vec3(2.0, 4.0, 5.0));
    
    const glm::vec3 c = mBox.mCenter;
    const glm::vec3 h = mBox.mHalfDimension;
    
    Geometry mGeometry({
        glm::vec3(c.x - h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y - h.y, c.z - h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z - h.z)
    });
    
    XCTAssert(mGeometry.Center() == mBox.mCenter);
}

- (void)testTranslate
{
    Triangle t = Triangle::XY();
    t.Translate(glm::vec3(0.0, 0.0, 1.0));
    Triangle triangle(glm::vec3(0.0, 0.0, 1.0),
                      glm::vec3(1.0, 0.0, 1.0),
                      glm::vec3(0.0, 1.0, 1.0));
    
    XCTAssert(triangle.IsEqual(t, kEpsilonSmall));
}

- (void)testScale
{
    Triangle t = Triangle::XY();
    t.Scale(glm::vec3(2.0, 2.0, 2.0), glm::vec3(0.0));
    Triangle triangle(glm::vec3(0.0, 0.0, 0.0),
                      glm::vec3(2.0, 0.0, 0.0),
                      glm::vec3(0.0, 2.0, 0.0));
    
    XCTAssert(triangle.IsEqual(t, kEpsilonSmall));
}




@end
