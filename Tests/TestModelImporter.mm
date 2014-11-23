
#import <XCTest/XCTest.h>

#import <ImportExport/ModelImporter.h>

using namespace ftr;

@interface TestModelImporter : XCTestCase

@end

@implementation TestModelImporter

- (void)setUp {
    [super setUp];
}

- (void)tearDown {
    [super tearDown];
}

- (void)testImport
{
    ModelImporter modelImporter;
    modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/X/dwarf.x");
}

@end
