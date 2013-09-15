//
//  FactoryEngine_Tests.m
//  FactoryEngine Tests
//
//  Created by Edvinas on 9/15/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface FactoryEngine_Tests : XCTestCase

@end

@implementation FactoryEngine_Tests

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

- (void)testExample
{
    ftr::Mat4 mat;
    XCTAssertTrue(NO, @"Fail");
}

@end
