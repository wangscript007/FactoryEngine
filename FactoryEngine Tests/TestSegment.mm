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

static const float kFloatAccuracy = 0.001;

@interface TestSegment : XCTestCase

@property (nonatomic, assign) glm::vec3 testPoint;
@property (nonatomic, assign) Segment segment;
@property (nonatomic, assign) Segment testSegment;
@property (nonatomic, assign) Segment testLine;

@end

@implementation TestSegment

- (void)setUp
{
    [super setUp];
    _testPoint = glm::vec3(2.0f, .0f, .0f);
    
    _segment.mStart = glm::vec3(2.0f, 2.0f, 2.0f);
    _segment.mEnd = glm::vec3(2.0f, 2.0f, -2.0f);
    
    _testSegment.mStart = glm::vec3(0.0f, 0.0f, 0.0f);
    _testSegment.mEnd = glm::vec3(4.0f, 0.0f, 0.0f);
    
    _testLine.mStart = glm::vec3(0.0f, 0.0f, 0.0f);
    _testLine.mEnd = glm::vec3(-1.0f, 0.0f, 0.0f);

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
    XCTAssertEqualWithAccuracy(result, expectedResult, kFloatAccuracy, @"");

}

- (void)testDistanceFromSegment
{
    float expectedResult = 2.0f;
    float result = _segment.DistanceFromSegment(_testSegment);
    XCTAssertEqualWithAccuracy(result, expectedResult, kFloatAccuracy, @"");
}

- (void)testDistanceFromLine
{
    float expectedResult = 2.0f;
    float result = _segment.DistanceFromLine(_testLine);
    XCTAssertEqualWithAccuracy(result, expectedResult, kFloatAccuracy, @"");
}

- (void)testShortestSegmentFromLine1
{
    Segment segment1;
    segment1.mStart = glm::vec3(0.0f, 0.0f, 0.0f);
    segment1.mEnd = glm::vec3(1.0f, 0.0f, 1.0f);
    
    Segment segment2;
    segment2.mStart = glm::vec3(1.0f, 0.0f, 0.0f);
    segment2.mEnd = glm::vec3(0.0f, 0.0f, 1.0f);
    
    const Segment& result = segment1.ShortestSegmentFromLine(segment2);
    Segment expectedResult;
    expectedResult.mStart = glm::vec3(0.5f, 0.0f, 0.5f);
    expectedResult.mEnd = glm::vec3(0.5f, 0.0f, 0.5f);
    XCTAssertTrue(expectedResult.mStart == result.mStart, @"");
    XCTAssertTrue(expectedResult.mEnd == result.mEnd, @"");
}

- (void)testShortestSegmentFromLine2
{
    Segment segment1;
    segment1.mStart = glm::vec3(0.0f, 1.0f, 0.0f);
    segment1.mEnd = glm::vec3(1.0f, 1.0f, 1.0f);
    
    Segment segment2;
    segment2.mStart = glm::vec3(1.0f, 0.0f, 0.0f);
    segment2.mEnd = glm::vec3(0.0f, 0.0f, 1.0f);
    
    const Segment& result = segment1.ShortestSegmentFromLine(segment2);
    Segment expectedResult;
    expectedResult.mStart = glm::vec3(0.5f, 1.0f, 0.5f);
    expectedResult.mEnd = glm::vec3(0.5f, 0.0f, 0.5f);
    XCTAssertTrue(expectedResult.mStart == result.mStart, @"");
    XCTAssertTrue(expectedResult.mEnd == result.mEnd, @"");
}

-(void)testIntersectsBox
{
    Box box = Box(glm::vec3(0.0f), glm::vec3(1.0f));
    
    
    Segment segment1;
    segment1.mStart = glm::vec3(1.0f, 1.0f, 1.0f);
    segment1.mEnd = glm::vec3(1.0f, 1.0f, -1.0f);
    
    XCTAssertTrue(segment1.IntersectsBox(box));
    
    Segment segment2;
    segment2.mStart = glm::vec3(2.0f, 2.0f, 2.0f);
    segment2.mEnd = glm::vec3(3.0f, 3.0f, 3.0f);
    
    XCTAssertTrue(segment2.IntersectsBox(box));
    
    Segment segment3;
    segment3.mStart = glm::vec3(0.5f, 0.0f, 2.0f);
    segment3.mEnd = glm::vec3(1.5f, 0.0f, 4.0f);
    
    XCTAssertTrue(segment3.IntersectsBox(box));
    
    
    
    
    Segment segment4;
    segment4.mStart = glm::vec3(2.0f, 1.0f, 1.0f);
    segment4.mEnd = glm::vec3(2.0f, 1.0f, -1.0f);
    
    XCTAssertFalse(segment4.IntersectsBox(box));
    
    Segment segment5;
    segment5.mStart = glm::vec3(-1.0f, 0.0f, 1.5f);
    segment5.mEnd = glm::vec3(1.0f, 0.0f, 2.5f);
    
    XCTAssertFalse(segment5.IntersectsBox(box));
    
    Segment segment6;
    segment6.mStart = glm::vec3(1.0f, 0.0f, -1.5f);
    segment6.mEnd = glm::vec3(4.0f, 0.0f, -0.5f);
    
    XCTAssertFalse(segment6.IntersectsBox(box));




}







@end
