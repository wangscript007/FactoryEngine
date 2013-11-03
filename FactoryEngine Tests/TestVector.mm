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
    
    XCTAssertTrue(Vector::IsCW(v1, v2), @"");
    XCTAssertFalse(Vector::IsCW(v1, v3), @"");
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
    
    XCTAssertTrue(Vector::IsCW(v1, v2), @"");
    XCTAssertFalse(Vector::IsCW(v1, v3), @"");
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
    
    XCTAssertTrue(Vector::IsCW(v1, v2), @"");
    XCTAssertFalse(Vector::IsCW(v1, v3), @"");
}



@end
