
#import <XCTest/XCTest.h>
#import <Processing/FaceExtruder.h>
#include <Processing/ModelEditor.h>

using namespace ftr;

@interface TestFaceExtruder : XCTestCase {
    ModelEditor* mModelEditor;
    
    FaceExtruder* mFaceExtruder;
}

@end


@implementation TestFaceExtruder

- (void)setUp
{
    [super setUp];
    mModelEditor = new ModelEditor();
    mFaceExtruder = new FaceExtruder(*mModelEditor);
}

- (void)tearDown
{
    FT_DELETE(mFaceExtruder);
    FT_DELETE(mModelEditor);
    [super tearDown];
}

- (void)testExtrudePrisme
{
    FaceNode* faceNode = new FaceNode({
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.1f, 1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    });
    mFaceExtruder->Extrude(*faceNode);
}

- (void)testExtrudeCube
{
    FaceNode* faceNode = new FaceNode({
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f)
    });
    
    std::vector<Edge*> edges = faceNode->GetEdges();
    for(int i = 0; i < edges.size(); ++i) {
        XCTAssert(edges[i]->twin()->IsFree());
    }
    
    mFaceExtruder->Extrude(*faceNode);
}


@end
