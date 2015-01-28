

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#include <Render/Primitive.h>

using namespace ftr;

@interface TestPrimitive : XCTestCase

@end

@implementation TestPrimitive

- (void)testSetDepth
{
    {
        Primitive primitive;
        char depth = 10;
        primitive.SetDepth(depth);
        char result = primitive.Depth();
        XCTAssert(result == depth);
    }
    {
        Primitive primitive;
        char depth = 255;
        primitive.SetDepth(depth);
        char result = primitive.Depth();
        XCTAssert(result == depth);
    }
    {
        Primitive primitive;
        char depth = 0;
        primitive.SetDepth(depth);
        char result = primitive.Depth();
        XCTAssert(result == depth);
    }
    {
        Primitive primitive;
        char depth = 10;
        primitive.SetDepth(depth);
        primitive.setOption(Primitive::kUseBlend, true);
        char result = primitive.Depth();
        XCTAssert(result == depth);
        XCTAssert(primitive.option(Primitive::kUseBlend));
    }

}

@end
