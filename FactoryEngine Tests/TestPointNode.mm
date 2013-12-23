//
//  TestPointNode.m
//  FactoryEngine
//
//  Created by Edvinas on 10/22/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Model/PointNode.h>
#include <Model/Edge.h>

using namespace ftr;

@interface TestPointNode : XCTestCase
{
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    PointNode* v5;
    PointNode* v6;
}

@end

@implementation TestPointNode

- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    v5 = new PointNode(glm::vec3(1.0f, -1.0f, 0.0f));
    v6 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";
    v6->mName = "6";
}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    [super tearDown];
}

- (void)testConnect1
{
    
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e63 = v6->ConnectTo(v3);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e13 = v1->ConnectTo(v3);
    
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e13->next(), e23->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e63->twin());
    XCTAssertEqual(e63->next(), e13->twin());
}

- (void)testConnect2
{
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e13 = v1->ConnectTo(v3);
    Edge* e63 = v6->ConnectTo(v3);
    
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e13->next(), e23->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e63->twin());
    XCTAssertEqual(e63->next(), e13->twin());
}

- (void)testConnect3
{
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e13 = v1->ConnectTo(v3);
    Edge* e63 = v6->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e13->next(), e23->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e63->twin());
    XCTAssertEqual(e63->next(), e13->twin());
}

- (void)testConnect4
{
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e31 = v3->ConnectTo(v1);
    Edge* e63 = v6->ConnectTo(v3);
    Edge* e21 = v2->ConnectTo(v1);
    Edge* e43 = v4->ConnectTo(v3);
    
    XCTAssertEqual(e21->next(), e31->twin());
    XCTAssertEqual(e31->next(), e21->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e63->twin());
    XCTAssertEqual(e63->next(), e31);
}

- (void)testConnect5
{
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e31 = v3->ConnectTo(v1);
    
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e43->next(), e31);
    XCTAssertEqual(e31->next(), e12);
}

- (void)testConnectThreeTriangles
{
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e31 = v3->ConnectTo(v1);
    Edge* e14 = v1->ConnectTo(v4);
    Edge* e54 = v5->ConnectTo(v4);
    Edge* e53 = v5->ConnectTo(v3);
    
    XCTAssertEqual(e23->next(), e53->twin());
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e43->next(), e31);
    XCTAssertEqual(e31->next(), e14);
    XCTAssertEqual(e14->next(), e43);
    XCTAssertEqual(e54->next(), e14->twin());
    XCTAssertEqual(e53->next(), e43->twin());
    XCTAssertEqual(e43->twin()->next(), e54->twin());
}

- (void)testConnectThreeTriangles2
{
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e45 = v4->ConnectTo(v5);
    Edge* e32 = v3->ConnectTo(v2);
    Edge* e31 = v3->ConnectTo(v1);
    Edge* e14 = v1->ConnectTo(v4);
    Edge* e53 = v5->ConnectTo(v3);
    
    XCTAssertEqual(e32->twin()->next(), e53->twin());
    XCTAssertEqual(e12->next(), e32->twin());
    XCTAssertEqual(e43->next(), e31);
    XCTAssertEqual(e31->next(), e14);
    XCTAssertEqual(e14->next(), e43);
    XCTAssertEqual(e45->twin()->next(), e14->twin());
    XCTAssertEqual(e53->next(), e43->twin());
    XCTAssertEqual(e43->twin()->next(), e45);
    
    XCTAssertEqual(e32->prev(), e31->twin());
    XCTAssertEqual(e12->prev(), e14->twin());
    XCTAssertEqual(e43->prev(), e14);
    XCTAssertEqual(e31->prev(), e43);
    XCTAssertEqual(e14->next(), e43);
    XCTAssertEqual(e45->prev(), e43->twin());
    XCTAssertEqual(e53->prev(), e45);
    XCTAssertEqual(e43->prev(), e14);

}




@end
