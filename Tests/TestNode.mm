//
//  TestNode.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 26/10/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import <Scene/Viewport.h>
#import <Processing/ModelEditor.h>
#import <Graph/GroupNode.h>

using namespace ftr;

@interface TestNode : XCTestCase

@property (nonatomic) Viewport viewport;
@property (nonatomic) ModelEditor* modelEditor;

@end

@implementation TestNode

- (void)setUp {
    [super setUp];
    _viewport.projectionMatrix = glm::mat4(glm::vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                           glm::vec4(0.000000, 0.000000, -0.200002, 0.000000));
    
    _viewport.modelviewMatrix = glm::mat4(glm::vec4(1.000000, 0.000000, 0.000000, 0.000000),
                                          glm::vec4(0.000000, 1.000000, 0.000000, 0.000000),
                                          glm::vec4(0.000000, 0.000000, 1.000000, 0.000000),
                                          glm::vec4(-3.749177, -2.357111, -12.031826, 1.000000));
    
    _viewport.frame = glm::vec4(0.000000, 0.000000, 1680.000000, 1680.000000);
    
    _modelEditor = new ModelEditor();
}

- (void)tearDown {
    FT_DELETE(_modelEditor);
    [super tearDown];
}

- (void)testSubnodesWithType
{
    _modelEditor->DebugCreateCube();
    std::vector<Node*> nodes;
    _modelEditor->activeGroup()->SubnodesWithType(Node::kFace, nodes);
    XCTAssert(nodes.size() == 6);
}

- (void)testFaceSubnodeWithCenterNearestToPoint
{
    _modelEditor->DebugCreateCube();
    GroupNode* group = _modelEditor->activeGroup();
    {
        Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(0.0, 0.0, 5.0), Node::kFace);
        
        XCTAssert(node->Type() == Node::kFace);
        XCTAssert(node->Center() == glm::vec3(0.0, 3.0, 3.0));
    }
    {
        Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(5.0, 0.0, 0.0), Node::kFace);
        
        XCTAssert(node->Type() == Node::kFace);
        XCTAssert(node->Center() == glm::vec3(2.0, 3.0, 0.0));
    }
    {
        Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(0.0, -5.0, 0.0), Node::kFace);
        
        XCTAssert(node->Type() == Node::kFace);
        XCTAssert(node->Center() == glm::vec3(0.0, 1.0, 0.0));
    }
}

- (void)testPointSubnodeWithCenterNearestToPointFace
{
    _modelEditor->DebugCreateCube();
    GroupNode* group = _modelEditor->activeGroup();
    {
        Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(1.0, 4.0, 5.0), Node::kPoint);
        
        XCTAssert(node->Type() == Node::kPoint);
        XCTAssert(node->Center() == glm::vec3(2.0, 5.0, 3.0));
    }
    {
        Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(-3.0, 10.0, -3.0), Node::kPoint);
        
        XCTAssert(node->Type() == Node::kPoint);
        XCTAssert(node->Center() == glm::vec3(-2.0, 5.0, -3.0));
    }
    {
        Node* node = group->SubnodeWithCenterNearestToPoint(glm::vec3(3.0, 0.0, -4.0), Node::kPoint);
        
        XCTAssert(node->Type() == Node::kPoint);
        XCTAssert(node->Center() == glm::vec3(2.0, 1.0, -3.0));
    }
}



@end
