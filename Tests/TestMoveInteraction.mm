

#import <XCTest/XCTest.h>
#include <Processing/ModelEditor.h>
#include <Interaction/MoveInteraction.h>
#include <Scene/Viewport.h>
#include <Graph/PointNode.h>
#include <Graph/LineNode.h>

using namespace ftr;

@interface TestMoveInteraction : XCTestCase

@property (nonatomic) MoveInteraction* interaction;
@property (nonatomic) Viewport viewport;
@property (nonatomic) ModelEditor* modelEditor;
@property (nonatomic) Camera* camera;


@end

@implementation TestMoveInteraction

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
    
    _modelEditor = new ModelEditor();
    _camera = new Camera(_viewport);
    _interaction = new MoveInteraction(*_modelEditor, *_camera);


}

- (void)tearDown
{
    FT_DELETE(_interaction);
    FT_DELETE(_modelEditor);
    FT_DELETE(_camera);
    [super tearDown];
}

- (void)testMoveTo
{
    _modelEditor->DebugCreateCube();
    std::vector<Node*> nodes;
    _modelEditor->activeGroup()->SubnodesWithType(Node::kFace, nodes);
    XCTAssert(nodes.size() == 6);
}

@end
