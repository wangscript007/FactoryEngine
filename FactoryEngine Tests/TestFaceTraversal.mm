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

@interface TestFaceTraversal : XCTestCase {
    FaceTraversal traversal;
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    PointNode* v5;
}

@end

@implementation TestFaceTraversal


- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    v5 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";

}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    [super tearDown];
}

- (void)testTwoTrianglesOrdered
{
    FaceNode* face = NULL;
    
    v1->ConnectTo(v2);
    face = traversal.TryToCreateFaceByConnectingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v2->ConnectTo(v3);
    face = traversal.TryToCreateFaceByConnectingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.TryToCreateFaceByConnectingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v4->ConnectTo(v3);
    face = traversal.TryToCreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v4);
    face = traversal.TryToCreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face != NULL);
    
    v5->ConnectTo(v4);
    face = traversal.TryToCreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face == NULL);
}

- (void)testTwoTrianglesUnordered
{
    FaceNode* face = NULL;
    
    v2->ConnectTo(v3);
    face = traversal.TryToCreateFaceByConnectingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v2);
    face = traversal.TryToCreateFaceByConnectingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v3);
    face = traversal.TryToCreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.TryToCreateFaceByConnectingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v1->ConnectTo(v4);
    face = traversal.TryToCreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face != NULL);
}

- (void)testQuadrate
{
    FaceNode* face = NULL;
    
    v2->ConnectTo(v3);
    face = traversal.TryToCreateFaceByConnectingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v2);
    face = traversal.TryToCreateFaceByConnectingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v3);
    face = traversal.TryToCreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v1);
    face = traversal.TryToCreateFaceByConnectingNode(*v4);
    XCTAssertTrue(face != NULL);
}



@end
