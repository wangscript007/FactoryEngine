//
//  TestEdge.m
//  FactoryEngine
//
//  Created by Edvinas on 26/10/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Model/PointNode.h>
#include <Model/Edge.h>

using namespace ftr;

@interface TestEdge : XCTestCase {
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    
    Edge* e12;
    Edge* e21;
    Edge* e23;
    Edge* e32;
    Edge* e34;
    Edge* e43;
    Edge* e13;
    Edge* e31;

}
@end

@implementation TestEdge



- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    
    e12 = new Edge(v1);
    e21 = new Edge(v2);
    e21->MakeTwinsWith(e12);
    v1->mEdge = e12;
    
    e23 = new Edge(v2);
    v2->mEdge = e23;
    e32 = new Edge(v3);
    v3->mEdge = e32;
    e23->MakeTwinsWith(e32);
    e12->ConnectToNext(e23);
    e32->ConnectToNext(e21);
    
    e34 = new Edge(v3);
    e43 = new Edge(v4);
    v4->mEdge = e43;
    e34->MakeTwinsWith(e43);
    e23->ConnectToNext(e34);
    e43->ConnectToNext(e32);
    
    e13 = new Edge(v1);
    e31 = new Edge(v3);
    e13->MakeTwinsWith(e31);
}

- (void)tearDown
{
    
    delete e12;
    delete e21;
    delete e23;
    delete e32;
    delete e43;
    delete e34;
    
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    [super tearDown];
}

- (void)testCWNeighbourWithOrigin
{
    Edge* CWNeighbour = e31->CWNeighbourWithSameOrigin();
    XCTAssertEqual(CWNeighbour, e32);
    
    CWNeighbour = e13->CWNeighbourWithSameOrigin();
    XCTAssertEqual(CWNeighbour, e12);
}


@end
