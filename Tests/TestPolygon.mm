

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
    
    glm::vec3 triangleNormal0 = polygon.GetTriangles()[0]->SurfaceNormal();
    glm::vec3 triangleNormal1 = polygon.GetTriangles()[1]->SurfaceNormal();
    XCTAssert(Vector::IsParallel(triangleNormal0, polygon.SurfaceNormal()));
    XCTAssert(Vector::IsParallel(triangleNormal1, polygon.SurfaceNormal()));
    
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
    
    Triangle* triangle0 = polygon.GetTriangles().at(0);
    Triangle* triangle1 = polygon.GetTriangles().at(1);
    
    glm::vec3 triangleNormal0 = triangle0->SurfaceNormal();
    glm::vec3 triangleNormal1 = triangle1->SurfaceNormal();
    glm::vec3 polygonNormal = polygon.SurfaceNormal();
    
    
    XCTAssert(Vector::IsParallel(triangleNormal0, polygonNormal));
    XCTAssert(Vector::IsParallel(triangleNormal1, polygonNormal));
}

@end
