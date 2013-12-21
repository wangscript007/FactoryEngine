//
//  TestFaceTraversal.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 15/12/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Model/PointNode.h>
#import <Model/Edge.h>
#import <Model/FaceNode.h>
#import <Model/FaceTraversal.h>

using namespace ftr;

@interface TestFaceTraversal : XCTestCase

@end

@implementation TestFaceTraversal

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testTwoTrianglesOrdered
{
    FaceTraversal traversal;
    
    PointNode* v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    PointNode* v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    PointNode* v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    PointNode* v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    PointNode* v5 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";
    
    FaceNode* face = NULL;
    
    v1->ConnectTo(v2);
    face = traversal.CreateFaceByConnectingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v2->ConnectTo(v3);
    face = traversal.CreateFaceByConnectingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.CreateFaceByConnectingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v4->ConnectTo(v3);
    face = traversal.CreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v4);
    face = traversal.CreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face != NULL);
    
    v5->ConnectTo(v4);
    face = traversal.CreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face == NULL);
}

- (void)testTwoTrianglesUnordered
{
    FaceTraversal traversal;
    
    PointNode* v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    PointNode* v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    PointNode* v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    PointNode* v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    PointNode* v5 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";
    
    FaceNode* face = NULL;
    
    
    v2->ConnectTo(v3);
    face = traversal.CreateFaceByConnectingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v2);
    face = traversal.CreateFaceByConnectingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v3);
    face = traversal.CreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.CreateFaceByConnectingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v1->ConnectTo(v4);
    face = traversal.CreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face != NULL);
    
  
}


@end
