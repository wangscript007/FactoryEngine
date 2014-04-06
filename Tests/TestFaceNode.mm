//
//  TestFaceNode.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 22/12/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Model/FaceNode.h>
#import <Processing/FaceTraversal.h>
#import <Geometry/Vector.h>
#include <Geometry/Constants.h>

using namespace ftr;


@interface TestFaceNode : XCTestCase {
    FaceNode* mFaceNode;
}

@end

@implementation TestFaceNode

- (void)setUp
{
    [super setUp];
    
    mFaceNode = new FaceNode(   {   glm::vec3(0.0f, 1.0f, 0.0f),
                                    glm::vec3(0.1f, 1.0f, 0.0f),
                                    glm::vec3(1.0f, 0.0f, 0.0f)
                                }
                             );
}

-(void)tearDown
{
    FT_DELETE(mFaceNode);
    [super tearDown];
}

- (void)testSurfaceNormal
{
    const glm::vec3 normal = mFaceNode->SurfaceNormal();
    XCTAssert(Vector::IsParallel(normal, kZAxis));
}




@end
