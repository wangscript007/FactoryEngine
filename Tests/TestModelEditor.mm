

#import <XCTest/XCTest.h>
#import <Processing/ModelEditor.h>

using namespace ftr;

@interface TestModelEditor : XCTestCase

@property (nonatomic, assign) ModelEditor modelEditor;


@end

@implementation TestModelEditor

- (void)setUp
{
    [super setUp];
}

- (void)tearDown
{
    [super tearDown];
}

- (void)testCreateCube
{
    _modelEditor.DebugCreateCube();
    XCTAssertEqual(6, _modelEditor.mDebugFacesCreated);
}

- (void)testCreatingFaces
{
    Box box(glm::vec3(0.0, 3.0, 0.0), glm::vec3(2.0, 2.0, 3.0));
    const glm::vec3 c = box.mCenter;
    const glm::vec3 h = box.mHalfDimension;
    
    glm::vec3 p[] = {
        glm::vec3(c.x - h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z + h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z + h.z),
        glm::vec3(c.x - h.x, c.y - h.y, c.z - h.z),
        glm::vec3(c.x - h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y + h.y, c.z - h.z),
        glm::vec3(c.x + h.x, c.y - h.y, c.z - h.z)
    };
    
    static const GLubyte indices[] = {
        0, 1,   1, 2,   2, 3,   3, 0,
        4, 5,   5, 6,   6, 7,   7, 4,
        0, 4,   1, 5,   2, 6,   3, 7
    };
    
    PointNode* nodes[8];
    for(int i = 0; i < 8; ++i) {
        nodes[i] = _modelEditor.CreatePoint(p[i]);
    }
    
    for (int i = 0; i < 12; i++) {
        PointNode* startPoint = nodes[indices[i*2]];
        PointNode* endPoint = nodes[indices[i*2+1]];
        _modelEditor.modelFactory()->CreateLine(startPoint, endPoint);
        PointNode::ConnectionResult result = startPoint->ConnectTo(endPoint);
        
        switch (i) {
            case 0:     XCTAssertEqual(result.count(), 0); break;
            case 1:     XCTAssertEqual(result.count(), 0); break;
            case 2:     XCTAssertEqual(result.count(), 0); break;
            case 3:     XCTAssertEqual(result.count(), 1); break;
            case 4:     XCTAssertEqual(result.count(), 0); break;
            case 5:     XCTAssertEqual(result.count(), 0); break;
            case 6:     XCTAssertEqual(result.count(), 0); break;
            case 7:     XCTAssertEqual(result.count(), 1); break;
            case 8:     XCTAssertEqual(result.count(), 0); break;
            case 9:     XCTAssertEqual(result.count(), 1); break;
            case 10:    XCTAssertEqual(result.count(), 1); break;
            case 11:    XCTAssertEqual(result.count(), 2); break;
            default:    XCTAssert(false); break;
        }
    }

}

@end
