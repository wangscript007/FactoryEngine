//
//  MathTest.m
//  FactoryEngine
//
//  Created by Edvinas on 9/15/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Utils/Picker.h>
#include <Scene/Camera.h>

using namespace ftr;

@interface MathTest : XCTestCase

@end

@implementation MathTest

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

- (void)testMatrixInvertion
{
    Mat4 original = Mat4(Vec4(1.0f, 0.0f, 0.0f, 1.0f),
                         Vec4(0.0f, 2.0f, 1.0f, 2.0f),
                         Vec4(2.0f, 1.0f, 0.0f, 1.0f),
                         Vec4(2.0f, 0.0f, 1.0f, 4.0f));
    Mat4 invert = original.Invert();
    Mat4 indentity;
    XCTAssertTrue(original*invert == indentity, @"Error in matrix invertion!");
}

- (void)testPicker
{
    
    Camera::Parameters parameters;
   
    parameters.projectionMatrix =       Mat4(Vec4(6.666667, 0.000000, 0.000000, 0.000000),
                                             Vec4(0.000000, 6.666667, 0.000000, 0.000000),
                                             Vec4(0.000000, 0.000000, -1.002002, -4.004004),
                                             Vec4(0.000000, 0.000000, -1.000000, 0.000000));

    
    parameters.modelviewMatrix =     Mat4(Vec4(-0.998705, 0.000000, -0.050872, 0.000000),
                                          Vec4(-0.023814, 0.883667, 0.467510, 0.000000),
                                          Vec4(0.044954, 0.468117, -0.882522, 0.000000),
                                          Vec4(0.000000, 0.000000, -10.000000, 1.000000));
    
    parameters.viewport = Frame(Vec2(0.0f, 0.0f), Vec2(400.0f, 400.0f));
    
    Vec3 testPoint = Vec3(200.0f, 200.0f, 0.5f);
    Vec3 projectVec     = Picker::GluProject(testPoint, parameters);
    Vec3 unprojectVec   = Picker::GluUnProject(projectVec, parameters);
    
    XCTAssertTrue(unprojectVec == testPoint, @"Error in GluProject or GluUnproject");
}


@end
