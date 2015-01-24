
#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#import <Graph/Vertex.h>
#import <Graph/Edge.h>
#import <Processing/FaceTraversal.h>

using namespace ftr;

@interface TestFaceTraversal : XCTestCase

@end

@implementation TestFaceTraversal

- (void)testTriangle
{
    Vertex vertex[3];
    vertex[0].mOrigin = glm::vec3(0);
    vertex[1].mOrigin = glm::vec3(0, 1, 0);
    vertex[2].mOrigin = glm::vec3(1, 0, 0);
    vertex[2].mOrigin = glm::vec3(1, 0, 0);
    
    for(int i = 0; i < 3; i++) {
        
        std::stringstream ss;
        ss << i;
        vertex[i].mName = ss.str();
    }
    
    vertex[0].ConnectTo(vertex[1]);
    vertex[1].ConnectTo(vertex[2]);
    vertex[2].ConnectTo(vertex[0]);
    
    
    
    FaceTraversal traversal(vertex[0]);
    FaceTraversal::Result result;
    traversal.Find(result);
    XCTAssert(result.Found());
}

- (void)testTwoTriangles
{
    FaceNode* face = new FaceNode();
    Vertex vertex[4];
    {
        vertex[0].mOrigin = glm::vec3(0);
        vertex[1].mOrigin = glm::vec3(0, 1, 0);
        vertex[2].mOrigin = glm::vec3(1, 0, 0);
        vertex[3].mOrigin = glm::vec3(1, 1, 0);
        
        for(int i = 0; i < 4; i++) {
            
            std::stringstream ss;
            ss << i;
            vertex[i].mName = ss.str();
        }
        
        vertex[0].ConnectTo(vertex[1]);
        vertex[1].ConnectTo(vertex[2]);
        vertex[2].ConnectTo(vertex[0]);
        
        FaceTraversal traversal(vertex[0]);
        FaceTraversal::Result result;
        traversal.Find(result);
        XCTAssert(result.Found());
        
        
        for (Edge *edge :result.mEdges) {
            edge->mFaces.push_back(face);
        }
    }

    {
        vertex[3].ConnectTo(vertex[1]);
        vertex[3].ConnectTo(vertex[2]);
        
        FaceTraversal traversal(vertex[1]);
        FaceTraversal::Result result;
        traversal.Find(result);
        XCTAssert(result.Found());
    }
    FT_DELETE(face);
}

- (void)testCube
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
    
    Vertex* nodes[8];
    for(int i = 0; i < 8; ++i) {
        nodes[i] = new Vertex();
        nodes[i]->mOrigin = p[i];
        std::stringstream ss;
        ss << i;
        nodes[i]->mName = ss.str();
    }
    
    for (int i = 0; i < 12; i++) {
        Vertex* startPoint = nodes[indices[i*2]];
        Vertex* endPoint = nodes[indices[i*2+1]];
        startPoint->ConnectTo(*endPoint);
        FaceTraversal traversal(*startPoint);
        FaceTraversal::Result result;
        int foundCount = 0;
        do {
            traversal.Find(result);
            if (result.Found()) {
                foundCount++;
                for (Edge *edge : result.mEdges) {
                    FaceNode* face = new FaceNode();
                    edge->mFaces.push_back(face);
                }
            }
        } while (result.Found());
        
        switch (i) {
            case 0:     XCTAssertEqual(foundCount, 0); break;
            case 1:     XCTAssertEqual(foundCount, 0); break;
            case 2:     XCTAssertEqual(foundCount, 0); break;
            case 3:     XCTAssertEqual(foundCount, 1); break;
            case 4:     XCTAssertEqual(foundCount, 0); break;
            case 5:     XCTAssertEqual(foundCount, 0); break;
            case 6:     XCTAssertEqual(foundCount, 0); break;
            case 7:     XCTAssertEqual(foundCount, 1); break;
            case 8:     XCTAssertEqual(foundCount, 0); break;
            case 9:     XCTAssertEqual(foundCount, 1); break;
            case 10:    XCTAssertEqual(foundCount, 1); break;
            case 11:    XCTAssertEqual(foundCount, 2); break;
            default:    XCTAssert(false); break;
        }
    }
    
    for(int i = 0; i < 8; ++i) {
        FT_DELETE(nodes[i]);
    }
}


@end
