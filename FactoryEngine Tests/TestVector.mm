//
//  TestVector.m
//  FactoryEngine
//
//  Created by Edvinas on 02/11/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Math/Vector.h>

using namespace ftr;

@interface TestVector : XCTestCase

@end

@implementation TestVector

- (void)setUp
{
    [super setUp];
    // Put setup code here; it will be run once, before the first test case.
}

- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

- (void)testIsCWInXYPlane
{
    glm::vec3 p1 = glm::vec3(0.0);
    glm::vec3 p2 = glm::vec3(1.0f, 1.0f, 0.0f);
    glm::vec3 p3 = glm::vec3(0.0f, 2.0f, 0.0f);
    glm::vec3 p4 = glm::vec3(2.0f, 0.0f, 0.0f);
    
    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p2;
    glm::vec3 v3 = p4 - p2;
    
    XCTAssertFalse(Vector::IsCWOrder(v1, v2));
    XCTAssertTrue(Vector::IsCWOrder(v1, v3));
}

- (void)testIsCWInXZPlane
{
    glm::vec3 p1 = glm::vec3(0.0);
    glm::vec3 p2 = glm::vec3(1.0f, 0.0f, 1.0f);
    glm::vec3 p3 = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 p4 = glm::vec3(2.0f, 0.0f, 0.0f);
    
    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p2;
    glm::vec3 v3 = p4 - p2;
    
    XCTAssertFalse(Vector::IsCWOrder(v1, v2));
    XCTAssertTrue(Vector::IsCWOrder(v1, v3));
}

- (void)testIsCWInYZPlane
{
    glm::vec3 p1 = glm::vec3(0.0);
    glm::vec3 p2 = glm::vec3(0.0f, 1.0f, 1.0f);
    glm::vec3 p3 = glm::vec3(0.0f, 0.0f, 2.0f);
    glm::vec3 p4 = glm::vec3(0.0f, 2.0f, 0.0f);
    
    glm::vec3 v1 = p2 - p1;
    glm::vec3 v2 = p3 - p2;
    glm::vec3 v3 = p4 - p2;
    
    XCTAssertFalse(Vector::IsCWOrder(v1, v2));
    XCTAssertTrue(Vector::IsCWOrder(v1, v3));
}

- (void)testCWAngle
{
    glm::vec3 v1 = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 v2 = glm::vec3(1.0f, 1.0f, 0.0f);
    glm::vec3 v3 = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 v4 = glm::vec3(0.0f, -1.0f, 0.0f);
    glm::vec3 v5 = glm::vec3(0.0f, 0.0f, 0.0f);
    
    glm::vec3 e53 = glm::normalize(v3 - v5);
    glm::vec3 e32 = glm::normalize(v2 - v3);
    glm::vec3 e31 = glm::normalize(v1 - v3);
    
    XCTAssertEqualWithAccuracy(Vector::CCWAngle(e53, e31), 135.0f, 0.01f);
    XCTAssertEqualWithAccuracy(Vector::CCWAngle(e53, e32), 90.0f, 0.01f);

}



@end
