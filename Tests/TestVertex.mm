//
//  TestVertex.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 07/02/2015.
//  Copyright (c) 2015 Dimention. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#import <Graph/Vertex.h>

using namespace ftr;

@interface TestVertex : XCTestCase

@end

@implementation TestVertex

- (void)testNeightboursInPlane
{
    Vertex v0 = Vertex(glm::vec3());
    Vertex v1 = Vertex(glm::vec3(1, 0, 0));
    Vertex v2 = Vertex(glm::vec3(0, 1, 0.5));
    Vertex v3 = Vertex(glm::vec3(0, 0, 1));

    v0.ConnectTo(v1);
    v0.ConnectTo(v2);
    v0.ConnectTo(v3);
    
    std::vector<Vertex*> neightbours;
    
    v0.Neighbours(neightbours, Triangle::XY());
    
    XCTAssert(neightbours.size() == 1);
    XCTAssert(neightbours[0] == &v1);
    
}

- (void)testCWNeighbourForNeighbour
{
    Vertex v0 = Vertex(glm::vec3());
    Vertex v1 = Vertex(glm::vec3(1, 0, 0));
    Vertex v2 = Vertex(glm::vec3(1, -1, 0));
    Vertex v3 = Vertex(glm::vec3(-1, -1, 0));
    
    v0.ConnectTo(v1);
    v0.ConnectTo(v2);
    
    {
        Vertex* nb = v0.CWNeighbourForNeighbour(v2, Triangle::XY());
        XCTAssert(nb == &v1);
    }
    {
        Vertex* nb = v0.CWNeighbourForNeighbour(v1, Triangle::XY());
        XCTAssert(nb == &v2);
    }
    
    v0.ConnectTo(v3);
    
    {
        Vertex* nb = v0.CWNeighbourForNeighbour(v1, Triangle::XY());
        XCTAssert(nb == &v2);
    }
    {
        Vertex* nb = v0.CWNeighbourForNeighbour(v2, Triangle::XY());
        XCTAssert(nb == &v3);
    }
    {
        Vertex* nb = v0.CWNeighbourForNeighbour(v3, Triangle::XY());
        XCTAssert(nb == &v1);
    }


    
}

@end
