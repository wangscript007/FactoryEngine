

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
    
    XCTAssert(polygon.DebugTrianglesMatchingPointsCount() == 6);
    
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
    
    XCTAssert(polygon.DebugTrianglesMatchingPointsCount() == 6);
}

- (void)testTriangulateRotated2
{
    ftr::Polygon polygon;

    polygon.AddPoint(glm::vec3(1.0, 0.0f, 3.0f));
    polygon.AddPoint(glm::vec3(1.0, 1.0f, 3.9f));
    polygon.AddPoint(glm::vec3(2.0, 1.0f, 3.9));
    polygon.AddPoint(glm::vec3(2.0, 0.0f, 3.0f));
    
    polygon.Triangulate();
    
    // four points should match
    
    
    polygon.DebugPrintTriangles();
    
    XCTAssert(polygon.GetTriangles().size() == 2);
    
    Triangle* triangle0 = polygon.GetTriangles().at(0);
    Triangle* triangle1 = polygon.GetTriangles().at(1);
    
    glm::vec3 triangleNormal0 = triangle0->SurfaceNormal();
    glm::vec3 triangleNormal1 = triangle1->SurfaceNormal();
    glm::vec3 polygonNormal = polygon.SurfaceNormal();
    
    XCTAssert(Vector::IsParallel(triangleNormal0, polygonNormal));
    XCTAssert(Vector::IsParallel(triangleNormal1, polygonNormal));
    
    XCTAssert(polygon.DebugTrianglesMatchingPointsCount() == 6);
}

- (void)testVec3WithoutComponent
{
    glm::vec3 vec(1, 2, 3);
    
    glm::vec2 v;
    v = ftr::Polygon::Vec3WithoutComponent(vec, 0);
    XCTAssert(v == glm::vec2(2, 3));
    
    v = ftr::Polygon::Vec3WithoutComponent(vec, 1);
    XCTAssert(v == glm::vec2(1, 3));
    
    v = ftr::Polygon::Vec3WithoutComponent(vec, 2);
    XCTAssert(v == glm::vec2(1, 2));
}

- (void)testVec2ByAppendingComponent
{
    glm::vec2 vec(1, 2);
    
    glm::vec3 v;
    
    v = ftr::Polygon::Vec2ByAppendingComponent(vec, 3, 0);
    XCTAssert(v == glm::vec3(3, 1, 2));
    
    v = ftr::Polygon::Vec2ByAppendingComponent(vec, 3, 1);
    XCTAssert(v == glm::vec3(1, 3, 2));
    
    v = ftr::Polygon::Vec2ByAppendingComponent(vec, 3, 2);
    XCTAssert(v == glm::vec3(1, 2, 3));

}

@end
