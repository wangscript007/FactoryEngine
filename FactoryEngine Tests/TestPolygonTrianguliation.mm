//
//  TestPolygonTrianguliation.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 23/03/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Model/PointNode.h>
#import <External/ConvexDecomposition/b2Polygon.h>

using namespace ftr;

@interface TestPolygonTrianguliation : XCTestCase
{
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    PointNode* v5;
    PointNode* v6;
}

@end

@implementation TestPolygonTrianguliation

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

- (void)testTrianguliation
{
    PointNode::ConnectionResult e23 = v2->ConnectTo(v3);
    PointNode::ConnectionResult e12 = v1->ConnectTo(v2);
    PointNode::ConnectionResult e43 = v4->ConnectTo(v3);
    PointNode::ConnectionResult e13 = v1->ConnectTo(v3);
    PointNode::ConnectionResult e53 = v5->ConnectTo(v3);
    PointNode::ConnectionResult e45 = v4->ConnectTo(v5);
    PointNode::ConnectionResult e41 = v4->ConnectTo(v1);
}

@end
