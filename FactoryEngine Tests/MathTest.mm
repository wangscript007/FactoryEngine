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
    glm::mat4 original = glm::mat4(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
                         glm::vec4(0.0f, 2.0f, 1.0f, 2.0f),
                         glm::vec4(2.0f, 1.0f, 0.0f, 1.0f),
                         glm::vec4(2.0f, 0.0f, 1.0f, 4.0f));
    glm::mat4 invert = glm::inverse(original);
    glm::mat4 indentity;
    XCTAssertTrue(original*invert == indentity, @"Error in matrix invertion!");

}

- (void)testPicker
{
    
    Camera::Parameters parameters;
   
    parameters.projectionMatrix =      glm::mat4(glm::vec4(1.732051, 0.000000, 0.000000, 0.000000),
                                            glm::vec4(0.000000, 1.732051, 0.000000, 0.000000),
                                            glm::vec4(0.000000, 0.000000, -1.000020, -1.000000),
                                            glm::vec4(0.000000, 0.000000, -0.200002, 0.000000));

    
    parameters.modelviewMatrix =     glm::mat4(glm::vec4(-0.902585, 0.000000, 0.430511, 0.000000),
                                          glm::vec4(0.336922, 0.622515, 0.706371, 0.000000),
                                          glm::vec4(-0.267999, 0.782608, -0.561873, 0.000000),
                                          glm::vec4(1.500000, -1.400000, -10.000000, 1.000000));
    
    parameters.viewport =  glm::vec4(glm::vec2(0.0f, 0.0f), glm::vec2(400.0f, 400.0f));
    
    glm::vec3 testPoint = glm::vec3(200.0f, 200.0f, 0.5f);
    glm::vec3 projectVec     = Picker::GluProject(testPoint, parameters);
    glm::vec3 unprojectVec   = Picker::GluUnProject(projectVec, parameters);
    
    const float accuracy = 0.1f;
    XCTAssertEqualWithAccuracy(testPoint.x, unprojectVec.x, accuracy, @"Project/unproject problem!");
    XCTAssertEqualWithAccuracy(testPoint.y, unprojectVec.y, accuracy, @"Project/unproject problem!");
    XCTAssertEqualWithAccuracy(testPoint.z, unprojectVec.z, accuracy, @"Project/unproject problem!");
    
}


@end
