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
    
    _parameters.modelviewMatrix = Mat4(Vec4(0.971681, 0.000000, 0.236295, 0.000000),
                                       Vec4(-0.131144, 0.831848, 0.539286, 0.000000),
                                       Vec4(-0.196562, -0.555003, 0.808291, 0.000000),
                                       Vec4(0.000000, 0.000000, -10.000000, 1.000000));
    
    _parameters.viewport = Frame(Vec2(0.000000, 0.000000), Vec2(1680.000000, 1680.000000));
}

- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

- (void)testExample
{
    InteractionAssistant assistant;
    Vec3 startScene = Vec3(2.0f, 0.0f, 0.0f);
    Vec2 endViewport = Vec2(1460.0f, 837.0f);
    Vec3 endScene = assistant.AxisAlignedViewport(startScene, endViewport, _parameters);
    
}

@end
