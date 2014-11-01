//
//  TestLineNode.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 01/11/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>
#include <Graph/LineNode.h>

using namespace ftr;

@interface TestLineNode : XCTestCase

@end

@implementation TestLineNode

- (void)testInvalidate
{
    ModelEditor editor;
    editor.DebugCreateCube();
    BodyNode* activeBody = editor.activeBody();
    
    std::vector<Node*> pointNodes;
    std::vector<Node*> lineNodes;
    std::vector<Node*> faceNodes;
    activeBody->SubnodesWithType(Node::kPoint, pointNodes);
    activeBody->SubnodesWithType(Node::kLine, lineNodes);
    activeBody->SubnodesWithType(Node::kFace, faceNodes);
    
    LineNode* lineNode = reinterpret_cast<LineNode*>(lineNodes[0]);
    
    lineNode->Invalidate(true);
    
    XCTAssertEqual(pointNodes.size(), 8);
    XCTAssertEqual(lineNodes.size(), 12);
    XCTAssertEqual(faceNodes.size(), 6);
    
    int invalidPointsCount = 0;
    for (auto& point : pointNodes) invalidPointsCount += point->invalid();
    XCTAssertEqual(invalidPointsCount, 2);
    
    int invalidLinesCount = 0;
    for (auto& line : lineNodes) invalidLinesCount += line->invalid();
    XCTAssertEqual(invalidLinesCount, 5);
    
    int invalidFacesCount = 0;
    for (auto& face : faceNodes) invalidFacesCount += face->invalid();
    XCTAssertEqual(invalidFacesCount, 4);
}


@end
