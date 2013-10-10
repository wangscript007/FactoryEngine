//
//  TestInteractionAssistant.m
//  FactoryEngine
//
//  Created by Edvinas on 10/6/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Scene/Camera.h>
#include <Interaction/InteractionAssistant.h>

using namespace ftr;

static const float kAccuracy = 0.3;

@interface TestInteractionAssistant : XCTestCase

@property (nonatomic, assign) ftr::Camera::Parameters parameters;

@end

@implementation TestInteractionAssistant

- (void)setUp
{
    [super setUp];
    _parameters.projectionMatrix = glm::mat4(glm::vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                         glm::vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                         glm::vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                         glm::vec4(0.000000, 0.000000, -0.200002, 0.000000));
    
    _parameters.modelviewMatrix = glm::mat4(glm::vec4(-1.000000, 0.000000, 0.000000, 0.000000),
                                       glm::vec4(0.000000, 0.990268, 0.139173, 0.000000),
                                       glm::vec4(0.000000, 0.139173, -0.990268, 0.000000),
                                       glm::vec4(0.000000, 0.000000, -10.000000, 1.000000));
    
    _parameters.viewport =  glm::vec4(0.000000, 0.000000, 920.000000, 920.000000);
    
}
- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

- (void)testAxisAlignedViewportX
{
    InteractionAssistant assistant;
    
    glm::vec3 startScene = glm::vec3(1.0f, 0.0f, -6.0f);
    glm::vec2 endViewport = glm::vec2(696.0f, 296.0f);
    glm::vec3 result = assistant.AxisAlignedViewport(startScene, endViewport, _parameters);
    glm::vec3 expectedResult = glm::vec3(-1.0f, 0.0f, -6.0f);

    XCTAssertEqualWithAccuracy(expectedResult.x, result.x, kAccuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.y, result.y, kAccuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.z, result.z, kAccuracy, @"");
}

- (void)testAxisAlignedViewportY
{
    InteractionAssistant assistant;
    
    glm::vec3 startScene = glm::vec3(-2.0f, 0.0f, 0.0f);
    glm::vec2 endViewport = glm::vec2(615.0f, 537.0f);
    glm::vec3 result = assistant.AxisAlignedViewport(startScene, endViewport, _parameters);
    glm::vec3 expectedResult = glm::vec3(-2.0f, 1.0f, 0.0f);
    
    XCTAssertEqualWithAccuracy(expectedResult.x, result.x, kAccuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.y, result.y, kAccuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.z, result.z, kAccuracy, @"");
}

- (void)testAxisAlignedViewportZ
{
    InteractionAssistant assistant;
    
    glm::vec3 startScene = glm::vec3(-3.0f, 0.0f, -2.0f);
    glm::vec2 endViewport = glm::vec2(858.0f, 381.0f);
    glm::vec3 result = assistant.AxisAlignedViewport(startScene, endViewport, _parameters);
    glm::vec3 expectedResult = glm::vec3(-3.0f, 0.0f, -4.0f);
    
    XCTAssertEqualWithAccuracy(expectedResult.x, result.x, kAccuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.y, result.y, kAccuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.z, result.z, kAccuracy, @"");

}


@end
