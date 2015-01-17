//
//  TestFaceReversal.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 07/06/14.
//  Copyright (c) 2014 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Processing/ModelEditor.h>
#import <Graph/PointNode.h>

using namespace ftr;

@interface TestFaceReversal : XCTestCase

@property (nonatomic, assign) ModelEditor modelEditor;

@end

@implementation TestFaceReversal

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

@end
