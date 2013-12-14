//
//  TestMutex.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 09/12/13.
//  Copyright (c) 2013 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>

@interface TestMutex : XCTestCase

@end

@implementation TestMutex

- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}




class Resource
{
public:
    Resource(): i(0) {}
    
    void use()
    {

        ++i;
    }
    
private:
    int i;

};

void thread_func(Resource& resource)
{
    resource.use();
}
- (void)testMutex
{
    Resource resource ;
}


@end
