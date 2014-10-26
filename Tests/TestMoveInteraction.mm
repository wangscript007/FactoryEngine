

#import <XCTest/XCTest.h>
#include <Processing/ModelEditor.h>
#include <Interaction/MoveInteraction.h>
#include <Scene/Viewport.h>
#include <Graph/PointNode.h>
#include <Graph/LineNode.h>
#include <Graph/GroupNode.h>

using namespace ftr;

@interface TestMoveInteraction : XCTestCase

@property (nonatomic) MoveInteraction* interaction;
@property (nonatomic) Viewport viewport;
@property (nonatomic) ModelEditor* modelEditor;


@end

@implementation TestMoveInteraction

- (void)setUp
{
    [super setUp];
    _viewport.projectionMatrix = glm::mat4(glm::vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                           glm::vec4(0.000000, 0.000000, -0.200002, 0.000000));
    
    _viewport.modelviewMatrix = glm::mat4(glm::vec4(1.000000, 0.000000, 0.000000, 0.000000),
                                          glm::vec4(0.000000, 1.000000, 0.000000, 0.000000),
                                          glm::vec4(0.000000, 0.000000, 1.000000, 0.000000),
                                          glm::vec4(-3.749177, -2.357111, -12.031826, 1.000000));
    
    _viewport.frame = glm::vec4(0.000000, 0.000000, 920.000000, 920.000000);
    
    _modelEditor = new ModelEditor();
    _interaction = new MoveInteraction(*_modelEditor, _viewport);


}

- (void)tearDown
{
    FT_DELETE(_interaction);
    FT_DELETE(_modelEditor);
    [super tearDown];
}

- (void)testSelect
{
     _modelEditor->DebugCreateCube();
    GroupNode* group = _modelEditor->activeGroup();
    
    Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(0.0, -5.0, 0.0), Node::kFace);
    
    XCTAssert(node->Type() == Node::kFace);
    XCTAssert(node->Center() == glm::vec3(0.0, 1.0, 0.0));
    
    _interaction->Select(node);
}

- (void)testMoveTo
{
    _modelEditor->DebugCreateCube();
    GroupNode* group = _modelEditor->activeGroup();
    
    Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(0.0, -5.0, 0.0), Node::kFace);
    
    XCTAssert(node->Type() == Node::kFace);
    XCTAssert(node->Center() == glm::vec3(0.0, 1.0, 0.0));
    
    _interaction->Select(node);
    
    _interaction->MoveTo(glm::vec2(460, 460));
    XCTAssert(glm::isNull(node->Center() - glm::vec3(3.7f, 2.3f, 0.0f), 0.1f));
    
    _interaction->MoveTo(glm::vec2(460, 460));
    XCTAssert(glm::isNull(node->Center() - glm::vec3(3.7f, 2.3f, 0.0f), 0.1f));
    
    
    
}

@end
