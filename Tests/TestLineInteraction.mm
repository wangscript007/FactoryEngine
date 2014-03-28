//
//  TestLineInteraction.m
//  FactoryEngine
//
//  Created by Edvinas on 10/12/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Processing/ModelEditor.h>
#include <Interaction/LineInteraction.h>
#include <Scene/Viewport.h>

using namespace ftr;

@interface TestLineInteraction : XCTestCase

@property (nonatomic) LineInteraction* lineInteraction;
@property (nonatomic) Viewport viewport;
@property (nonatomic) ModelEditor* modelEditor;

@end

@implementation TestLineInteraction

- (void)setUp
{
    [super setUp];
    _viewport.projectionMatrix = glm::mat4(glm::vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                           glm::vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                           glm::vec4(0.000000, 0.000000, -0.200002, 0.000000));
    
    _viewport.modelviewMatrix = glm::mat4(glm::vec4(-0.319405, -0.787539, 0.527032, 0.000000),
                                          glm::vec4(0.000000, 0.556165, 0.831072, 0.000000),
                                          glm::vec4(-0.947618, 0.265449, -0.177642, 0.000000),
                                          glm::vec4(-2.089686, 0.449766, -12.551600, 1.000000));
    
    _viewport.frame = glm::vec4(0.000000, 0.000000, 1680.000000, 1680.000000);
    
    Viewport::mDebugPoints.push_back(glm::vec3(779.417969, 729.011719, 0.991431)); // glm::vec3(1.013757, -0.000978, -2.034651)
    Viewport::mDebugPoints.push_back(glm::vec3(1145.417969, 621.011719, 0.991026)); // glm::vec3(1.008763, -0.000977, -5.010907)
    Viewport::mDebugPoints.push_back(glm::vec3(774.246094, 715.984375, 0.991379)); // glm::vec3(1.140808, 0.003359, -2.037147) 
    Viewport::mDebugPoints.push_back(glm::vec3(627.246094, 375.984375, 0.990102)); // glm::vec3(3.989027, 0.002965, -1.992242) 


    
    _modelEditor = new ModelEditor();
    _lineInteraction = new LineInteraction(*_modelEditor, _viewport);
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    Viewport::mDebugPoints.clear();
    FT_DELETE(_modelEditor);
    [super tearDown];
}

- (void)testPointSnap
{
    _lineInteraction->Begin();
    _lineInteraction->setStart([self debugAtIndex:0]);
    _lineInteraction->setEnd([self debugAtIndex:1]);
    _lineInteraction->Step();
    _lineInteraction->Finish();
    
    glm::vec3 start1 = _lineInteraction->start();
    glm::vec3 end1 = _lineInteraction->end();
    
    _lineInteraction->Begin();
    _lineInteraction->setStart([self debugAtIndex:2]);
    _lineInteraction->setEnd([self debugAtIndex:3]);
    _lineInteraction->Step();
    _lineInteraction->Finish();
    
    glm::vec3 start2 = _lineInteraction->start();
    glm::vec3 end2 = _lineInteraction->end();
    
    XCTAssertEqualWithAccuracy(start1.x, start2.x, 0.0001f, @"");
    XCTAssertEqualWithAccuracy(start1.y, start2.y, 0.0001f, @"");
    XCTAssertEqualWithAccuracy(start1.z, start2.z, 0.0001f, @"");
}

- (void)testAxisSnap
{
    _lineInteraction->Begin();
    _lineInteraction->setStart([self debugAtIndex:0]);
    _lineInteraction->setEnd([self debugAtIndex:1]);
    _lineInteraction->Step();
    _lineInteraction->Finish();
    
    XCTAssertEqualWithAccuracy(_lineInteraction->end().x, _lineInteraction->start().x, 0.0001,
                               @"Line should be z axis aligned");
}

- (void)testAxisSnapNotSnapping
{
    _lineInteraction->Begin();
    _lineInteraction->setStart([self debugAtIndex:1]);
    _lineInteraction->setEnd([self debugAtIndex:3]);
    _lineInteraction->Step();
    _lineInteraction->Finish();
    
    XCTAssertEqualWithAccuracy(_lineInteraction->start().x, 1.0, 0.1, @"");
    XCTAssertEqualWithAccuracy(_lineInteraction->start().z, -5.0, 0.1, @"");
    
    XCTAssertEqualWithAccuracy(_lineInteraction->end().x, 3.9, 0.1, @"");
    XCTAssertEqualWithAccuracy(_lineInteraction->end().z, -1.99, 0.1, @"");

}


- (glm::vec2)debugAtIndex:(int)index
{
    const glm::vec3& point = Viewport::mDebugPoints[index];
    return glm::vec2(point.x, point.y);
}

@end
