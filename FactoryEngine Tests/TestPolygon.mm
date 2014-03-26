

#import <XCTest/XCTest.h>
#include <Geometry/Polygon.h>
#include <Geometry/Vector.h>

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

- (void)testRotationToSurfaceNormal
{
    ftr::Polygon polygon;
    polygon.AddPoint(glm::vec3(0.0, 0.0f, 0.0f));
    polygon.AddPoint(glm::vec3(0.0, 1.0f, 1.0f));
    polygon.AddPoint(glm::vec3(1.0, 1.0f, 1.0));
    polygon.AddPoint(glm::vec3(1.0, 0.0f, 0.0f));
    
    
    glm::vec3 targetNormal = glm::vec3(0.0f, 0.0f, 1.0f);
    polygon.RotateToSurfaceNormal(targetNormal);
    polygon.DebugPrint();
    XCTAssert(Vector::IsParallel(polygon.SurfaceNormal(), targetNormal));
    
}

- (void)testTriangulateAxisAligned
{
    ftr::Polygon polygon;
    polygon.AddPoint(glm::vec3(0.0, 0.0f, 0.0f));
    polygon.AddPoint(glm::vec3(0.0, 1.0f, 0.0f));
    polygon.AddPoint(glm::vec3(1.0, 1.0f, 0.0f));
    polygon.AddPoint(glm::vec3(1.0, 0.0f, 0.0f));
    
    polygon.Triangulate();
    XCTAssert(polygon.GetTriangles().size() == 2);
    polygon.DebugPrintTriangles();
    
}

- (void)testTriangulateRotated
{
    ftr::Polygon polygon;
    polygon.AddPoint(glm::vec3(0.0, 0.0f, 0.0f));
    polygon.AddPoint(glm::vec3(0.0, 1.0f, 0.9f));
    polygon.AddPoint(glm::vec3(1.0, 1.0f, 0.9));
    polygon.AddPoint(glm::vec3(1.0, 0.0f, 0.0f));
    
    polygon.Triangulate();
    
    polygon.DebugPrintTriangles();
    
    XCTAssert(polygon.GetTriangles().size() == 2);
    XCTAssert(Vector::IsParallel(polygon.GetTriangles()[0]->SurfaceNormal(), polygon.SurfaceNormal()));
    XCTAssert(Vector::IsParallel(polygon.GetTriangles()[1]->SurfaceNormal(), polygon.SurfaceNormal()));
}

@end
