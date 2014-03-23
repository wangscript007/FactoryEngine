
#import <XCTest/XCTest.h>
#include <Model/PointNode.h>
#include <poly2tri.h>

using namespace ftr;

@interface TestPoly2tri : XCTestCase

@end

@implementation TestPoly2tri

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testTrianguliation
{
    std::vector<p2t::Point*> polyline;
    
    polyline.push_back(new p2t::Point(0.0, 1.0));
    polyline.push_back(new p2t::Point(1.0, 1.0));
    polyline.push_back(new p2t::Point(1.0, 0.0));
    polyline.push_back(new p2t::Point(0.0,-1.0));
    
    p2t::CDT *cdt = new p2t::CDT(polyline);
    cdt->Triangulate();
    std::vector<p2t::Triangle*> triangles = cdt->GetTriangles();
    
    XCTAssert(triangles.size() == 2);
    
}

@end
