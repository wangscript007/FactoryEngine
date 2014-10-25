

#import <XCTest/XCTest.h>
#import <Scene/Viewport.h>

using namespace ftr;

@interface TestViewport : XCTestCase

@property (nonatomic, assign) Viewport viewport;

@end

@implementation TestViewport

- (void)tearDown
{
    [super tearDown];
}

- (void)orientateCameraFrontToXYPlane
{
    // Forward vector perpendicular to XY
    _viewport.projectionMatrix = glm::mat4(glm::vec4(2.144507, 0.000000, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 2.144507, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 0.000000, -1.002002, -1.000000),
                                           glm::vec4(0.000000, 0.000000, -2.002002, 0.000000));
    
    _viewport.modelviewMatrix = glm::mat4(glm::vec4(1.000000, 0.000000, 0.000000, 0.000000),
                                          glm::vec4(0.000000, 1.000000, 0.000000, 0.000000),
                                          glm::vec4(0.000000, 0.000000, 1.000000, 0.000000),
                                          glm::vec4(-3.749177, -2.357111, -12.031826, 1.000000));
    
    _viewport.frame = glm::vec4(0.000000, 0.000000, 920.000000, 920.000000);
}

- (void)orientateCameraFrontToOtherPlane
{
    _viewport.projectionMatrix = glm::mat4(glm::vec4(2.144507, 0.000000, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 2.144507, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 0.000000, -1.002002, -1.000000),
                                           glm::vec4(0.000000, 0.000000, -2.002002, 0.000000));
    
    _viewport.modelviewMatrix = glm::mat4(glm::vec4(0.615662, -0.243509, 0.749443, 0.000000),
                                          glm::vec4(0.000000, 0.951057, 0.309017, 0.000000),
                                          glm::vec4(-0.788011, -0.190250, 0.585529, 0.000000),
                                          glm::vec4(-0.707124, -0.942234, -14.727875, 1.000000));
    
    _viewport.frame = glm::vec4(0.000000, 0.000000, 920.000000, 920.000000);
}

- (void)testPlaneAtCoords
{
    {
        [self orientateCameraFrontToXYPlane];
        glm::vec3 sceneCoords(0.0f, 0.0f, 0.0f);
        Triangle plane = _viewport.Plane();
        XCTAssert(plane.Cross() != glm::vec3());
    }
    
    {
        [self orientateCameraFrontToXYPlane];
        Triangle plane(glm::vec3(0.0, 0.0, 1.0),
                       glm::vec3(0.0, 1.0, 1.0),
                       glm::vec3(1.0, 1.0, 1.0));
        
        Triangle testPlane = _viewport.Plane();
        
        XCTAssert(testPlane.IsParallelTo(plane));
    }
    
    {
        [self orientateCameraFrontToOtherPlane];
        Triangle plane(glm::vec3(0.0, 0.0, 1.0),
                       glm::vec3(0.0, 1.0, 1.0),
                       glm::vec3(1.0, 1.0, 1.0));
        
        Triangle testPlane = _viewport.Plane();
        
        XCTAssertFalse(testPlane.IsParallelTo(plane));
    }
    
}


@end
