//
//  TestFaceReversal.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 07/06/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Processing/ModelEditor.h>
#import <Processing/FaceReversal.h>
#import <Graph/PointNode.h>

using namespace ftr;

@interface TestFaceReversal : XCTestCase

@property (nonatomic, assign) ModelEditor modelEditor;

@end

@implementation TestFaceReversal

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testReverse
{
    Box box(glm::vec3(0.0, 3.0, 0.0), glm::vec3(2.0, 2.0, 3.0));
    const glm::vec3 c = box.mCenter;
    const glm::vec3 h = box.mHalfDimension;
    
    glm::vec3 p[] = {
        glm::vec3(c.x - h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y - h.y, c.z - h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z - h.z)
    };
    
    static const GLubyte indices[] = {
        0, 1,   1, 2,   2, 3,   3, 0,
        4, 5,   5, 6,   6, 7,   7, 4,
        0, 4,   1, 5,   2, 6,   3, 7
    };
    
    PointNode* nodes[8];
    for(int i = 0; i < 8; ++i) {
        nodes[i] = _modelEditor.CreatePoint(p[i]);
        std::stringstream ss;
        ss << i;
        nodes[i]->mName = ss.str();
    }
    
    for (int i = 0; i < 12; i++) {
        PointNode* startPoint = nodes[indices[i*2]];
        PointNode* endPoint = nodes[indices[i*2+1]];
        _modelEditor.modelFactory()->CreateLine(startPoint, endPoint);
        PointNode::ConnectionResult result = startPoint->ConnectTo(endPoint);
        
        if (i == 7) {
            FaceReversal faceReversal;
            faceReversal.ReverseIslandStartingAtNode(*result.edge->targetNode());
            XCTAssertEqual(faceReversal.stats().visitedNodes, 4);
            XCTAssertEqual(faceReversal.stats().reversedEdges, 4);
            
            faceReversal.ReverseIslandStartingAtNode(*result.edge->targetNode());
            XCTAssertEqual(faceReversal.stats().visitedNodes, 4);
            XCTAssertEqual(faceReversal.stats().reversedEdges, 4);
            
            faceReversal.ReverseIslandStartingAtNode(*result.edge->targetNode());
            XCTAssertEqual(faceReversal.stats().visitedNodes, 4);
            XCTAssertEqual(faceReversal.stats().reversedEdges, 4);
        }

        
        switch (i) {
            case 0:     XCTAssertEqual(result.count(), 0); break;
            case 1:     XCTAssertEqual(result.count(), 0); break;
            case 2:     XCTAssertEqual(result.count(), 0); break;
            case 3:     XCTAssertEqual(result.count(), 1); break;
            case 4:     XCTAssertEqual(result.count(), 0); break;
            case 5:     XCTAssertEqual(result.count(), 0); break;
            case 6:     XCTAssertEqual(result.count(), 0); break;
            case 7:     XCTAssertEqual(result.count(), 1); break;
            case 8:     XCTAssertEqual(result.count(), 0); break;
            case 9:     XCTAssertEqual(result.count(), 1); break;
            case 10:    XCTAssertEqual(result.count(), 1); break;
            case 11:    XCTAssertEqual(result.count(), 2); break;
            default:    XCTAssert(false); break;
        }
    }

    XCTAssert(YES, @"Pass");
}

- (void)testPerformanceExample {
    // This is an example of a performance test case.
    [self measureBlock:^{
        // Put the code you want to measure the time of here.
    }];
}

@end
