

#import <XCTest/XCTest.h>
#include <Geometry/Polygon.h>

using namespace ftr;

@interface TestPolygon : XCTestCase

@end

@implementation TestPolygon

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testTriangulate
{
    ftr::Polygon polygon;
    polygon.AddPoint(glm::vec3(0.0, 0.0f, 0.0f));
    polygon.AddPoint(glm::vec3(0.0, 1.0f, 0.0f));
    polygon.AddPoint(glm::vec3(1.0, 1.0f, 0.0f));
    polygon.AddPoint(glm::vec3(1.0, 0.0f, 0.0f));
    
    polygon.Triangulate();
    
    
    
}

@end
