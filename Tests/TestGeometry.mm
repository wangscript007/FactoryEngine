
#import <XCTest/XCTest.h>
#import <Geometry/Geometry.h>
#import <Geometry/GeometryPrimitives.h>


using namespace ftr;

@interface TestGeometry : XCTestCase {
    Geometry* mGeometry;
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
    
    mGeometry = new Geometry({
        glm::vec3(c.x - h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y - h.y, c.z - h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z - h.z)
    });
    
    XCTAssert(mGeometry->Center() == mBox.mCenter);
    
    FT_DELETE(mGeometry);
    
}

@end
