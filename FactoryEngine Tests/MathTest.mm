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
   
    parameters.projectionMatrix =      Mat4(Vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                            Vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                            Vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                            Vec4(0.000000, 0.000000, -0.200002, 0.000000));

    
    parameters.modelviewMatrix =     Mat4(Vec4(-0.902585, 0.000000, 0.430511, 0.000000),
                                          Vec4(0.336922, 0.622515, 0.706371, 0.000000),
                                          Vec4(-0.267999, 0.782608, -0.561873, 0.000000),
                                          Vec4(1.500000, -1.400000, -10.000000, 1.000000));
    
    parameters.viewport = Frame(Vec2(0.0f, 0.0f), Vec2(400.0f, 400.0f));
    
    Vec3 testPoint = Vec3(200.0f, 200.0f, 0.5f);
    Vec3 projectVec     = Picker::GluProject(testPoint, parameters);
    Vec3 unprojectVec   = Picker::GluUnProject(projectVec, parameters);
    
    const float accuracy = 0.1f;
    XCTAssertEqualWithAccuracy(testPoint.mX, unprojectVec.mX, accuracy, @"Project/unproject problem!");
    XCTAssertEqualWithAccuracy(testPoint.mY, unprojectVec.mY, accuracy, @"Project/unproject problem!");
    XCTAssertEqualWithAccuracy(testPoint.mZ, unprojectVec.mZ, accuracy, @"Project/unproject problem!");
    
}


@end
