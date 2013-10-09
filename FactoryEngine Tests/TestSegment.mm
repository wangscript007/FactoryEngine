//
//  TestSegment.m
//  FactoryEngine
//
//  Created by Edvinas on 10/9/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <Math/Segment.h>

using namespace ftr;

@interface TestSegment : XCTestCase

@property (nonatomic, assign) glm::vec3 testPoint;
@property (nonatomic, assign) Segment segment;

@end

@implementation TestSegment

- (void)setUp
{
    [super setUp];
    _testPoint = glm::vec3(2.0f, .0f, .0f);
    _segment.mStart = glm::vec3(2.0f, 2.0f, 2.0f);
    _segment.mEnd = glm::vec3(2.0f, 2.0f, -2.0f);

}

- (void)tearDown
{
    // Put teardown code here; it will be run once, after the last test case.
    [super tearDown];
}

- (void)testNearestPoint
{
    glm::vec3 expectedResult = glm::vec3(2.0f, 2.0f, 0.0f);
    glm::vec3 result = _segment.NearestPoint(_testPoint);
    XCTAssertTrue(expectedResult == result, @"");
}

- (void)testDistanceFromPoint
{
    float expectedResult = 2.0f;
    float result = _segment.DistanceFromPoint(_testPoint);
    XCTAssertEqualWithAccuracy(result, expectedResult, 0.001f, @"");
}


@end
