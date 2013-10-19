//
//  TestCylinderBoxIntersection.m
//  FactoryEngine
//
//  Created by Edvinas on 10/16/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Math/Cylinder.h>

using namespace ftr;

@interface TestCylinderBoxIntersection : XCTestCase

@end

@implementation TestCylinderBoxIntersection

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

- (void)testIntesection
{
    const Box& box = Box(glm::vec3(0.0f), glm::vec3(0.5f));
    {
        const Segment& segment = Segment(glm::vec3(1.0f, 1.0f, 1.0f),
                                         glm::vec3(1.0f, 1.0f, -1.0f));
        const Cylinder& cylinder = Cylinder(segment, 1.0f);
        XCTAssertTrue(cylinder.Intersects(box));
    }
    {
        const Segment& segment = Segment(glm::vec3(1.0f, 1.0f, 1.0f),
                                         glm::vec3(1.0f, -1.0f, 1.0f));
        const Cylinder& cylinder = Cylinder(segment, 0.51f);
        XCTAssertTrue(cylinder.Intersects(box));
    }
    {
        const Segment& segment = Segment(glm::vec3(4.0f, 4.0f, 4.0f),
                                         glm::vec3(5.0f, 5.0f, 5.0f));
        const Cylinder& cylinder = Cylinder(segment, 0.001f);
        XCTAssertTrue(cylinder.Intersects(box));
    }

    
    {
        const Segment& segment = Segment(glm::vec3(1.0f, 1.0f, 1.0f),
                                          glm::vec3(-1.0f, 1.0f, 1.0f));
        const Cylinder& cylinder = Cylinder(segment, 0.49f);
        XCTAssertFalse(cylinder.Intersects(box));
    }
    {
        const Segment& segment = Segment(glm::vec3(4.0f, 4.0f, 4.0f),
                                         glm::vec3(10.0f, 10.0f, 5.0f));
        const Cylinder& cylinder = Cylinder(segment, 0.001f);
        XCTAssertFalse(cylinder.Intersects(box));
    }



 
    
}

@end
