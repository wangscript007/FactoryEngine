

#import <XCTest/XCTest.h>
#import <Model/PointNode.h>
#import <Model/Edge.h>
#import <Model/FaceNode.h>
#import <Processing/FaceTraversal.h>
#import <random>

using namespace ftr;

@interface TestFaceTraversal : XCTestCase {
//    FaceTraversal traversal;
    PointNode* v1;
    PointNode* v2;
    PointNode* v3;
    PointNode* v4;
    PointNode* v5;
    PointNode* v2h;
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
    v2h = new PointNode(glm::vec3(1.0f, 1.0f, 2.0f));
    
    v1->mName = "1";
    v2->mName = "2";
    v3->mName = "3";
    v4->mName = "4";
    v5->mName = "5";
    v2h->mName = "2h";

}

- (void)tearDown
{
    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v2h;
    [super tearDown];
}

- (void)testTwoTriangles3D
{
    FaceNode* face = NULL;
    
    v1->ConnectTo(v3);
    
    v3->ConnectTo(v4);
    
    v4->ConnectTo(v1);
    
    v1->ConnectTo(v2h);
    
    v2h->ConnectTo(v3);
    
}

- (void)testTwoTrianglesOrdered
{
    FaceNode* face = NULL;
    
    v1->ConnectTo(v2);
    
    
    
    v2->ConnectTo(v3);
    
    
    
    v3->ConnectTo(v1);
    
    
    
    v4->ConnectTo(v3);
    
    
    v1->ConnectTo(v4);
    
    
    v5->ConnectTo(v4);
    
}






- (void)testConnectingInRandomOrder
{
    return;
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
            
            PointNode::ConnectionResult result = p1->ConnectTo(p2);
            facesCount += result.count();
        }
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
    
    v1->ConnectTo(v2);
    
    v4->ConnectTo(v3);
    
    v4->ConnectTo(v1);
    
}



@end
