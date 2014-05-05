//
//  TestColorPickingMapper.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 26/04/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Processing/ColorPickingMapper.h>

using namespace ftr;

@interface TestColorPickingMapper : XCTestCase

@end

@implementation TestColorPickingMapper

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testColorFromInt1
{
    glm::vec3 color(1.0, 0.0, 0.0);
    int number = ColorPickingMapper::IntFromColor(color);
    glm::vec3 result = ColorPickingMapper::ColorFromInt(number);
    XCTAssert(result == color);
}
    
- (void)testColorFromInt2
{
    glm::vec3 color(0.0, 0.0, 1.0);
    int number = ColorPickingMapper::IntFromColor(color);
    glm::vec3 result = ColorPickingMapper::ColorFromInt(number);
    XCTAssert(result == color);
}
    
- (void)testColorFromInt3
{
    glm::vec3 color(1.0, 1.0, 1.0);
    int number = ColorPickingMapper::IntFromColor(color);
    glm::vec3 result = ColorPickingMapper::ColorFromInt(number);
    XCTAssert(result == color);

}

- (void)testColorFromInt4
{
    glm::vec3 color(13/255.0f, 18/255.0f, 255/255.0f);
    int number = ColorPickingMapper::IntFromColor(color);
    glm::vec3 result = ColorPickingMapper::ColorFromInt(number);
    XCTAssert(result == color);
    
}

- (void)testIntFromColor
{
    int number = 10004;
    glm::vec3 color = ColorPickingMapper::ColorFromInt(number);
    int result = ColorPickingMapper::IntFromColor(color);
    XCTAssert(result == number);
}

@end
