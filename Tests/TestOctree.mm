//
//  TestOctree.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 02/11/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <XCTest/XCTest.h>

#include <Processing/Octree.h>

using namespace ftr;

@interface TestOctree : XCTestCase
{
    PointNode* _points[8];
}

@end

@implementation TestOctree




- (void)setUp
{
    [super setUp];
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
    
    for(int i = 0; i < 8; ++i) {
        PointNode* point = new PointNode();
        point->mOrigin = p[i];
        _points[i] = point;
    }
}

- (void)tearDown
{
    for (int i = 0; i < 8; i++) {
        FT_DELETE(_points[i]);
    }
    [super tearDown];
}



- (void)testInsertPoint
{

    
}

- (void)testRemovePoint
{
    
}

- (void)testUpdatePoint
{
    ftr::Octree octree(Box(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(100.0f, 100.0f, 100.0f)));
    
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 8; ++j) {
            _points[j]->mOrigin.x += 10.0f;
            _points[j]->mOrigin.z += 0.0f;
            _points[j]->mOrigin.y += 0.0f;
            octree.UpdatePoint(_points[j]);
        }
    }
    
    
    
}




@end
