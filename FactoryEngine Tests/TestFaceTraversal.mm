//
//  TestFaceTraversal.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 15/12/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Model/PointNode.h>
#import <Model/Edge.h>
#import <Model/FaceNode.h>
#import <Model/FaceTraversal.h>
#import <random>

using namespace ftr;

@interface TestFaceTraversal : XCTestCase {
    FaceTraversal traversal;
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    PointNode* v5;
}

@end

@implementation TestFaceTraversal


- (void)setUp
{
    [super setUp];
    v1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
    v2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
    v3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
    v4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
    v5 = new PointNode(glm::vec3(1.0f, -1.0f, 0.0f));
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";

}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    [super tearDown];
}

- (void)testTwoTrianglesOrdered
{
    FaceNode* face = NULL;
    
    v1->ConnectTo(v2);
    face = traversal.FindAndCreateFaceContainingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v2->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.FindAndCreateFaceContainingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v4->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v4);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face != NULL);
    
    v5->ConnectTo(v4);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face == NULL);
}

- (void)testTwoTrianglesUnordered
{
    FaceNode* face = NULL;
    
    v2->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v2);
    face = traversal.FindAndCreateFaceContainingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.FindAndCreateFaceContainingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v1->ConnectTo(v4);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face != NULL);
}

- (void)testThreeTrianglesUnordered
{
    FaceNode* face = NULL;
    
    v2->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v2);
    face = traversal.FindAndCreateFaceContainingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.FindAndCreateFaceContainingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v1->ConnectTo(v4);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face != NULL);
    
    v5->ConnectTo(v4);
    face = traversal.FindAndCreateFaceContainingNode(*v5);
    XCTAssertTrue(face == NULL);
    
    v5->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v3);
    XCTAssertTrue(face != NULL);
}

- (void)testThreeTrianglesUnordered2
{
    FaceNode* face = NULL;
    
    v1->ConnectTo(v2);
    face = traversal.FindAndCreateFaceContainingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v5);
    face = traversal.FindAndCreateFaceContainingNode(*v5);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v2);
    face = traversal.FindAndCreateFaceContainingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v3->ConnectTo(v1);
    face = traversal.FindAndCreateFaceContainingNode(*v3);
    XCTAssertTrue(face != NULL);
    
    v1->ConnectTo(v4);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face != NULL);
    
    v5->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v3);
    XCTAssertTrue(face != NULL);
}

- (void)testConnectingIncidentFaces
{
    v1->ConnectTo(v2);
    traversal.FindAndCreateFaceContainingNode(*v1);
    v2->ConnectTo(v3);
    traversal.FindAndCreateFaceContainingNode(*v3);
    v3->ConnectTo(v1);
    traversal.FindAndCreateFaceContainingNode(*v1);
    v3->ConnectTo(v4);
    traversal.FindAndCreateFaceContainingNode(*v3);
    v1->ConnectTo(v4);
    traversal.FindAndCreateFaceContainingNode(*v1);
}

- (void)testConnectingIncidentFaces2
{
    v3->ConnectTo(v5);
    traversal.FindAndCreateFaceContainingNode(*v1);
    v3->ConnectTo(v4);
    traversal.FindAndCreateFaceContainingNode(*v3);
    v1->ConnectTo(v2);
    traversal.FindAndCreateFaceContainingNode(*v1);
    v4->ConnectTo(v1);
    traversal.FindAndCreateFaceContainingNode(*v3);
    v2->ConnectTo(v3);
    traversal.FindAndCreateFaceContainingNode(*v1);
    v3->ConnectTo(v1);
    traversal.FindAndCreateFaceContainingNode(*v1);
}


- (void)testConnectingInRandomOrder
{
    for (int i = 0; i < 1000; i++) {
        PointNode* xv1 = new PointNode(glm::vec3(0.0f, 1.0f, 0.0f));
        PointNode* xv2 = new PointNode(glm::vec3(1.0f, 1.0f, 0.0f));
        PointNode* xv3 = new PointNode(glm::vec3(1.0f, 0.0f, 0.0f));
        PointNode* xv4 = new PointNode(glm::vec3(0.0f, -1.0f, 0.0f));
        PointNode* xv5 = new PointNode(glm::vec3(1.0f, -1.0f, 0.0f));
        xv1->mName = "1";
        xv2->mName = "2";
        xv3->mName = "3";
        xv4->mName = "4";
        xv5->mName = "5";
        
        
        std::random_device rd;
        std::mt19937 g(rd());
        
        std::vector<std::pair<PointNode*, PointNode*>> edges;
        edges.push_back(std::make_pair(xv1, xv2));
        edges.push_back(std::make_pair(xv2, xv3));
        edges.push_back(std::make_pair(xv3, xv1));
        edges.push_back(std::make_pair(xv3, xv4));
        edges.push_back(std::make_pair(xv3, xv5));
        edges.push_back(std::make_pair(xv4, xv1));
        edges.push_back(std::make_pair(xv4, xv5));
 
        
        std::shuffle(edges.begin(), edges.end(), g);
        printf("============== TEST %i ===============\n", i);
        for(auto it = edges.begin(); it != edges.end(); ++it) {
            PointNode* p1 = (*it).first;
            PointNode* p2 = (*it).second;
            printf("%s - %s\n", p1->mName.c_str(), p2->mName.c_str());
            if (rand() % 2 == 0) {
                std::swap((*it).first, (*it).second);
            }
        }
        
        int facesCount = 0;
        for(auto it = edges.begin(); it != edges.end(); ++it) {
            PointNode* p1 = (*it).first;
            PointNode* p2 = (*it).second;
            p1->ConnectTo(p2);
            if (traversal.FindAndCreateFaceContainingNode(*p1)) {
                facesCount++;
            }
            if (traversal.FindAndCreateFaceContainingNode(*p2)) {
                facesCount++;
            }
        }
        assert(3 == facesCount);
        XCTAssertEqual(3, facesCount);
        
        delete xv1;
        delete xv2;
        delete xv3;
        delete xv4;
        delete xv5;
    }
}



- (void)testQuadrate
{
    FaceNode* face = NULL;
    
    v2->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v2);
    XCTAssertTrue(face == NULL);
    
    v1->ConnectTo(v2);
    face = traversal.FindAndCreateFaceContainingNode(*v1);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v3);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face == NULL);
    
    v4->ConnectTo(v1);
    face = traversal.FindAndCreateFaceContainingNode(*v4);
    XCTAssertTrue(face != NULL);
}



@end
