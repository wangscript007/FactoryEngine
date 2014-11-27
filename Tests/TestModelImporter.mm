
#import <XCTest/XCTest.h>

#import <ImportExport/ModelImporter.h>
#import <Processing/ModelEditor.h>

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
    [self measureBlock:^{
        ModelEditor modelEditor;
        ModelImporter modelImporter(modelEditor);
        
        modelImporter.Import("/Users/edvinassarkus/factory/factoryengine/Tests/Models/X/dwarf.x");

    }];
}

@end
