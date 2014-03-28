//
//  TestPointNode.m
//  FactoryEngine
//
//  Created by Edvinas on 10/22/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#include <Model/PointNode.h>
#include <Processing/PointNodeIterator.h>
#include <Model/Edge.h>

using namespace ftr;

@interface TestPointNode : XCTestCase
{
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    PointNode* v5;
    PointNode* v6;
}

@end

@implementation TestPointNode

- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    v5 = new PointNode(glm::vec3(1.0f, -1.0f, 0.0f));
    v6 = new PointNode(glm::vec3(0.0f, 0.0f, 0.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";
    v6->mName = "6";
}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    [super tearDown];
}

- (void)testConnect1
{
    
    PointNode::ConnectionResult e12 = v1->ConnectTo(v2);
    PointNode::ConnectionResult e23 = v2->ConnectTo(v3);
    PointNode::ConnectionResult e31 = v3->ConnectTo(v1);
    
    XCTAssert(e31.faceA || e31.faceB);
}

- (void)testConnect2
{
    PointNode::ConnectionResult e12 = v1->ConnectTo(v2);
    PointNode::ConnectionResult e23 = v2->ConnectTo(v3);
    PointNode::ConnectionResult e13 = v1->ConnectTo(v3);
    XCTAssert(e13.faceA ||  e13.faceB);
    
    PointNode::ConnectionResult e53 = v5->ConnectTo(v3);
    PointNode::ConnectionResult e43 = v4->ConnectTo(v3);
    XCTAssert(e43.faceA ||  e43.faceB);
    
    PointNode::ConnectionResult e45 = v4->ConnectTo(v5);
    PointNode::ConnectionResult e41 = v4->ConnectTo(v1);
    XCTAssert(e41.faceA ||  e41.faceB);
}

- (void)testConnect3
{
    PointNode::ConnectionResult e12 = v1->ConnectTo(v2);
    PointNode::ConnectionResult e23 = v2->ConnectTo(v3);
    PointNode::ConnectionResult e31 = v3->ConnectTo(v1);
    PointNode::ConnectionResult e34 = v3->ConnectTo(v4);
    PointNode::ConnectionResult e41 = v4->ConnectTo(v1);
    
    XCTAssert(e31.faceA || e31.faceB);
    XCTAssert(e41.faceA || e41.faceB);
}

- (void)testConnect4
{
    PointNode::ConnectionResult e12 = v1->ConnectTo(v2);
    PointNode::ConnectionResult e23 = v2->ConnectTo(v3);
    PointNode::ConnectionResult e34 = v3->ConnectTo(v4);
    PointNode::ConnectionResult e41 = v4->ConnectTo(v1);
    
    XCTAssert(e41.faceA || e41.faceB);
}

- (void)testIteratorOperations
{
    PointNode::ConnectionResult e21 = v2->ConnectTo(v1, true);
    PointNode::ConnectionResult e31 = v3->ConnectTo(v1, true);
    PointNode::ConnectionResult e41 = v4->ConnectTo(v1, true);
    
    v1->Insert(v1->Begin(), *e31.edge);
    v1->Insert(v1->Begin(), *e41.edge);
    v1->Move(v1->Begin(), v1->End());
    v1->Move(v1->Begin(), v1->End());
    v1->Move(v1->Begin(), v1->End());
    v1->Move(*(e21.edge->twin()), ++v1->Begin());
    v1->Move(*(e21.edge->twin()), v1->End());
    
    if (!v1->IsEmpty()) {
        PointNode::Iterator it = v1->Begin();
        int i = 0;
        for(; it != v1->End(); ++it) {
            Edge* edge = (*it);
            printf("Edge %s is at index %d\n", edge->Name().c_str(), i);
            i++;
        }
        it = v1->End();
        --it;
        i--;
        for(; it != v1->End(); --it) {
            Edge* edge = (*it);
            printf("Edge %s is at index %d\n", edge->Name().c_str(), i);
            i--;
        }
    }
    v1->Remove(v1->Begin());
    v1->Remove(v1->Begin());
    v1->Remove(v1->Begin());
    XCTAssert(v1->IsEmpty());
}




@end
