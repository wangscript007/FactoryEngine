//
//  MathTest.m
//  FactoryEngine
//
//  Created by Edvinas on 9/15/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>

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
    ftr::Mat4 original = ftr::Mat4(ftr::Vec4(1.0f, 0.0f, 0.0f, 1.0f),
                                   ftr::Vec4(0.0f, 2.0f, 1.0f, 2.0f),
                                   ftr::Vec4(2.0f, 1.0f, 0.0f, 1.0f),
                                   ftr::Vec4(2.0f, 0.0f, 1.0f, 4.0f));
    ftr::Mat4 invert = original.Invert();
    ftr::Mat4 indentity;
    XCTAssertTrue(original*invert == indentity, @"Error in matrix invertion!");
}

@end
