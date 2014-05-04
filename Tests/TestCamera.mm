

#import <XCTest/XCTest.h>
#import <Scene/Camera.h>
#import <Scene/Viewport.h>

using namespace ftr;

@interface TestCamera : XCTestCase

@property (nonatomic) Viewport viewport;
@property (nonatomic) Camera* camera;

@end

@implementation TestCamera

- (void)setUp
{
    [super setUp];
    _viewport.projectionMatrix = glm::mat4(glm::vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                           glm::vec4(0.000000, 0.000000, -0.200002, 0.000000));
    
    _viewport.modelviewMatrix = glm::mat4(glm::vec4(-0.319405, -0.787539, 0.527032, 0.000000),
                                          glm::vec4(0.000000, 0.556165, 0.831072, 0.000000),
                                          glm::vec4(-0.947618, 0.265449, -0.177642, 0.000000),
                                          glm::vec4(-2.089686, 0.449766, -12.551600, 1.000000));
    
    _viewport.frame = glm::vec4(0.000000, 0.000000, 1680.000000, 1680.000000);
    
    _camera = new Camera(_viewport);
}

- (void)tearDown
{
    FT_DELETE(_camera);
    [super tearDown];
}

- (void)testExample
{
    
}

@end
