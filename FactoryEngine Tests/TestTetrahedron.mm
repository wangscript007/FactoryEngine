//
//  TestTetrahedron.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 27/12/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Model/PointNode.h>
#import <Model/Edge.h>
#import <Model/FaceTraversal.h>

using namespace ftr;

@interface TestTetrahedron : XCTestCase
{
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* l4;
    PointNode* h4;
    FaceTraversal traversal;
}

@end

@implementation TestTetrahedron

- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 0.0f, -0.7f));
    v2 = new PointNode(glm::vec3(0.5f, 0.0f, 0.3f));
    v3 = new PointNode(glm::vec3(-0.5f, 0.0f, 0.3f));
    l4 = new PointNode(glm::vec3(0.0f, 0.3f, 0.0f)); // low
    h4 = new PointNode(glm::vec3(0.0f, 3.0f, 0.0f)); // high
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    l4->mName = "L4";
    h4->mName = "H4";
    
}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete l4;
    delete h4;
    [super tearDown];
}

- (void)testConnectingLowTetrahedron
{
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e31 = v3->ConnectTo(v1);
    XCTAssertTrue(traversal.FindAndCreateFaceContainingNode(*v3));
    Edge* e14 = v1->ConnectTo(l4);
    Edge* e34 = v3->ConnectTo(l4);
    XCTAssertTrue(traversal.FindAndCreateFaceContainingNode(*v3));
    Edge* e24 = v2->ConnectTo(l4);
    XCTAssertTrue(traversal.FindAndCreateFaceContainingNode(*v3));
    
//    XCTAssertEqual(e12->twin()->next(), e14);
    XCTAssertEqual(e23->twin()->next(), e12->twin());
  //  XCTAssertEqual(e31->twin()->next(), e34);
}

- (void)testConnectingHighTetrahedron
{
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e31 = v3->ConnectTo(v1);
//    Edge* e14 = v1->ConnectTo(h4);
//    Edge* e24 = v2->ConnectTo(h4);
//    Edge* e34 = v3->ConnectTo(h4);
    
    XCTAssertEqual(e12->twin()->next(), e31->twin());
    XCTAssertEqual(e23->twin()->next(), e12->twin());
    XCTAssertEqual(e31->twin()->next(), e23->twin());

}

@end
