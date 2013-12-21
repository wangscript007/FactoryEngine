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

@end

@implementation TestPointNode

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

- (void)testConnect1
{
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
    
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e53 = v5->ConnectTo(v3);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e13 = v1->ConnectTo(v3);
    
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e13->next(), e23->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e53->twin());
    XCTAssertEqual(e53->next(), e13->twin());
    
    
    delete v1;
    delete v2;
    delete v3;
    delete v4;
}

- (void)testConnect2
{
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
    
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e13 = v1->ConnectTo(v3);
    Edge* e53 = v5->ConnectTo(v3);
    
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e13->next(), e23->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e53->twin());
    XCTAssertEqual(e53->next(), e13->twin());
    
    
    delete v1;
    delete v2;
    delete v3;
    delete v4;
}

- (void)testConnect3
{
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
    
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e13 = v1->ConnectTo(v3);
    Edge* e53 = v5->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    
    XCTAssertEqual(e12->next(), e23);
    XCTAssertEqual(e13->next(), e23->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e53->twin());
    XCTAssertEqual(e53->next(), e13->twin());
    
    
    delete v1;
    delete v2;
    delete v3;
    delete v4;
}

- (void)testConnect4
{
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
    
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e31 = v3->ConnectTo(v1);
    Edge* e53 = v5->ConnectTo(v3);
    Edge* e21 = v2->ConnectTo(v1);
    Edge* e43 = v4->ConnectTo(v3);
    
    XCTAssertEqual(e21->next(), e31->twin());
    XCTAssertEqual(e31->next(), e21->twin());
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e53->twin());
    XCTAssertEqual(e53->next(), e31);
    
    
    delete v1;
    delete v2;
    delete v3;
    delete v4;
}

- (void)testConnect5
{
    PointNode* v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    PointNode* v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    PointNode* v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    PointNode* v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    
    Edge* e23 = v2->ConnectTo(v3);
    Edge* e12 = v1->ConnectTo(v2);
    Edge* e43 = v4->ConnectTo(v3);
    Edge* e31 = v3->ConnectTo(v1);
    
    XCTAssertEqual(e31->next(), e12);
    XCTAssertEqual(e23->next(), e43->twin());
    XCTAssertEqual(e43->next(), e31);
    XCTAssertEqual(e12->next(), e23);
}




@end
