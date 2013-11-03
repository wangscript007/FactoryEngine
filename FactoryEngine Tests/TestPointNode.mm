//
//  TestPointNode.m
//  FactoryEngine
//
//  Created by Edvinas on 10/22/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Model/PointNode.h>
#include <Model/HalfEdge.h>

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

- (void)testHalfEdgeReverse
{
    PointNode* v1 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    PointNode* v2 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    PointNode* v3 = new PointNode(glm::vec3(1.0f, 0.0f, 1.0f));
    
    v1->ConnectTo(v2);
    v2->ConnectTo(v3);
    v3->ConnectTo(v1);
    
    HalfEdge* e1 = v1->halfEdge();
    HalfEdge* prev = e1;
    
    HalfEdge* e2 = e1->next();
    HalfEdge* e3 = e2->next();
    XCTAssertEqual(e3->next(), e1);
    
    e1->Reverse();
    e2->Reverse();
    e3->Reverse();
    
    prev = prev->prev();
    prev = prev->prev();
    prev = prev->prev();
    XCTAssertEqual(prev, e1);
    
    XCTAssertEqual(v1->halfEdge()->twin()->prev()->twin(), v1->halfEdge()->next());
    XCTAssertEqual(v2->halfEdge()->twin()->prev()->twin(), v2->halfEdge()->next());
    XCTAssertEqual(v3->halfEdge()->twin()->prev()->twin(), v3->halfEdge()->next());
    
    delete v1;
    delete v2;
    delete v3;
}

- (void)testOrderedConnect
{
    PointNode* v1 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    PointNode* v2 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    PointNode* v3 = new PointNode(glm::vec3(1.0f, 0.0f, 1.0f));
    
    v1->ConnectTo(v2);
    v2->ConnectTo(v3);
    v3->ConnectTo(v1);
    
    HalfEdge* initial = v1->halfEdge();
    HalfEdge* next = initial;
    HalfEdge* prev = initial;
    next = next->next();
    XCTAssertTrue(next->IsClockwiseFrom(*next->prev()));
    next = next->next();
    XCTAssertTrue(next->IsClockwiseFrom(*next->prev()));
    next = next->next();
    XCTAssertTrue(next->IsClockwiseFrom(*next->prev()));
    XCTAssertEqual(next, initial);
    
    prev = prev->prev();
    prev = prev->prev();
    prev = prev->prev();
    XCTAssertEqual(prev, initial);
    
    XCTAssertEqual(v1->halfEdge()->twin()->prev()->twin(), v1->halfEdge()->next());
    XCTAssertEqual(v2->halfEdge()->twin()->prev()->twin(), v2->halfEdge()->next());
    XCTAssertEqual(v3->halfEdge()->twin()->prev()->twin(), v3->halfEdge()->next());
    
    delete v1;
    delete v2;
    delete v3;
}

- (void)testUnorderedConnect
{
    PointNode* v1 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    PointNode* v2 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    PointNode* v3 = new PointNode(glm::vec3(1.0f, 0.0f, 1.0f));
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    
    v2->ConnectTo(v1);
    v2->ConnectTo(v3);
    v1->ConnectTo(v3);
    
    HalfEdge* initial = v1->halfEdge();
    HalfEdge* next = initial;
    HalfEdge* prev = initial;
    next = next->next();
    next = next->next();
    next = next->next();
    XCTAssertEqual(next, initial);
    
    prev = prev->prev();
    prev = prev->prev();
    prev = prev->prev();
    XCTAssertEqual(prev, initial);
    
    XCTAssertEqual(v1->halfEdge()->twin()->prev()->twin(), v1->halfEdge()->next());
    XCTAssertEqual(v2->halfEdge()->twin()->prev()->twin(), v2->halfEdge()->next());
    XCTAssertEqual(v3->halfEdge()->twin()->prev()->twin(), v3->halfEdge()->next());
    
    
    delete v1;
    delete v2;
    delete v3;

}

@end
