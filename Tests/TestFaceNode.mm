

#import <XCTest/XCTest.h>
#import <Graph/FaceNode.h>
#import <Processing/FaceTraversal.h>
#import <Geometry/Vector.h>
#include <Geometry/Constants.h>

using namespace ftr;


@interface TestFaceNode : XCTestCase {
}

@end

@implementation TestFaceNode


- (void)testSurfaceNormal
{
    FaceNode face({     glm::vec3(0.0f, 1.0f, 0.0f),
                        glm::vec3(0.1f, 1.0f, 0.0f),
                        glm::vec3(1.0f, 0.0f, 0.0f)
    });
    const glm::vec3 normal = face.SurfaceNormal();
    XCTAssert(Vector::IsParallel(normal, kZAxis));
}

- (void)testCenter
{
    {
        FaceNode face({     glm::vec3(0.0f, 0.0f, 0.0f),
                            glm::vec3(1.0f, 0.0f, 0.0f),
                            glm::vec3(1.0f, 1.0f, 0.0f),
                            glm::vec3(0.0f, 1.0f, 0.0f)
        });
        
        const glm::vec3 center = face.Center();
        XCTAssert(center == glm::vec3(0.5, 0.5, 0.0));
    }
    {
        FaceNode face({     glm::vec3(0.0f, 0.0f, 1.0f),
            glm::vec3(1.0f, 0.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(0.0f, 1.0f, 1.0f)
        });
        
        const glm::vec3 center = face.Center();
        XCTAssert(center == glm::vec3(0.5, 0.5, 1.0));
    }
}

@end
