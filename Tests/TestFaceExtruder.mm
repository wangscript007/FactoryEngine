
#import <XCTest/XCTest.h>
#import <Processing/FaceExtruder.h>
#include <Processing/ModelEditor.h>

using namespace ftr;

@interface TestFaceExtruder : XCTestCase {
    ModelEditor* mModelEditor;
    FaceNode* mFaceNode;
    FaceExtruder* mFaceExtruder;
}

@end


@implementation TestFaceExtruder

- (void)setUp
{
    [super setUp];
    mModelEditor = new ModelEditor();
    mFaceNode = new FaceNode({
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.1f, 1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    });
    mFaceExtruder = new FaceExtruder(*mModelEditor);
}

- (void)tearDown
{
    FT_DELETE(mFaceExtruder);
    FT_DELETE(mFaceNode);
    FT_DELETE(mModelEditor);
    [super tearDown];
}

- (void)testExtrude
{
    mFaceExtruder->Extrude(*mFaceNode);
    
}

@end
