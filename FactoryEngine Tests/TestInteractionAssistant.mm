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

@interface TestInteractionAssistant : XCTestCase

@property (nonatomic, assign) ftr::Camera::Parameters parameters;

@end

@implementation TestInteractionAssistant

- (void)setUp
{
    [super setUp];
    _parameters.projectionMatrix = Mat4(Vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                         Vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                         Vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                         Vec4(0.000000, 0.000000, -0.200002, 0.000000));
    
    _parameters.modelviewMatrix = Mat4(Vec4(-1.000000, 0.000000, 0.000000, 0.000000),
                                       Vec4(0.000000, 0.990268, 0.139173, 0.000000),
                                       Vec4(0.000000, 0.139173, -0.990268, 0.000000),
                                       Vec4(0.000000, 0.000000, -10.000000, 1.000000));
    
    _parameters.viewport = Frame(Vec2(0.000000, 0.000000), Vec2(920.000000, 920.000000));
    
}
- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

- (void)testAxisAlignedViewportX
{
    InteractionAssistant assistant;
    const float accuracy = 0.1f;
    
    Vec3 startScene = Vec3(1.0f, 0.0f, -6.0f);
    Vec2 endViewport = Vec2(696.0f, 296.0f);
    Vec3 result = assistant.AxisAlignedViewport(startScene, endViewport, _parameters);
    Vec3 expectedResult = Vec3(-1.0f, 0.0f, -6.0f);

    XCTAssertEqualWithAccuracy(expectedResult.mX, result.mX, accuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.mY, result.mY, accuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.mZ, result.mZ, accuracy, @"");
}

- (void)testAxisAlignedViewportY
{
    InteractionAssistant assistant;
    const float accuracy = 0.1f;
    
    Vec3 startScene = Vec3(-2.0f, 0.0f, 0.0f);
    Vec2 endViewport = Vec2(615.0f, 537.0f);
    Vec3 result = assistant.AxisAlignedViewport(startScene, endViewport, _parameters);
    Vec3 expectedResult = Vec3(-2.0f, 1.0f, 0.0f);
    
    XCTAssertEqualWithAccuracy(expectedResult.mX, result.mX, accuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.mY, result.mY, accuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.mZ, result.mZ, accuracy, @"");
}

- (void)testAxisAlignedViewportZ
{
    InteractionAssistant assistant;
    const float accuracy = 0.1f;
    
    Vec3 startScene = Vec3(-3.0f, 0.0f, -2.0f);
    Vec2 endViewport = Vec2(858.0f, 381.0f);
    Vec3 result = assistant.AxisAlignedViewport(startScene, endViewport, _parameters);
    Vec3 expectedResult = Vec3(-3.0f, 0.0f, -4.0f);
    
    XCTAssertEqualWithAccuracy(expectedResult.mX, result.mX, accuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.mY, result.mY, accuracy, @"");
    XCTAssertEqualWithAccuracy(expectedResult.mZ, result.mZ, accuracy, @"");

}


@end
