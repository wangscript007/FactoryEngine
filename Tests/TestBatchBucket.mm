//
//  TestBatchBucket.m
//  FactoryEngine
//
//  Created by Edvinas Sarkus on 06/01/15.
//  Copyright (c) 2015 Dimention. All rights reserved.
//

#import <XCTest/XCTest.h>
#import <Render/BatchBucket.h>
#import <Render/PolygonBatch.h>
#import <Render/LineRenderer.h>
#import <Render/Batch.h>

using namespace ftr;

@interface TestBatchBucket : XCTestCase

@end

@implementation TestBatchBucket


- (void)testAddPrimitive
{
    BatchBucket bucket;
    for (int i = 0; i < bucket.batchSizeLimit()*10; ++i) {
        PolygonPrimitive* polygonPrimitive = new PolygonPrimitive();
        bucket.AddPrimitive(*polygonPrimitive);
    }
    
    BatchBucket::DebugData data = bucket.GetDebugData();
    XCTAssertEqual(data.mPolygonsData.primitivesCount, bucket.batchSizeLimit()*10);
    XCTAssertEqual(data.mPolygonsData.batchesCount, 10);
    XCTAssertEqual(data.mLinesData.primitivesCount, 0);
    XCTAssertEqual(bucket.batchCount(), 10);
    
    bucket.Clear();
}

- (void)testDeleteBatch
{
    BatchBucket bucket;
    for (int i = 0; i < bucket.batchSizeLimit()*10-1; ++i) {
        PolygonPrimitive* polygonPrimitive = new PolygonPrimitive();
        bucket.AddPrimitive(*polygonPrimitive);
    }
    
    PolygonPrimitive* polygon1 = new PolygonPrimitive();
    PolygonPrimitive* polygon2 = new PolygonPrimitive();
    polygon1->setOption(Primitive::kUseBlend, true);
    Batch* batch1 = bucket.AddPrimitive(*polygon1);
    Batch* batch2 = bucket.AddPrimitive(*polygon2);
    BatchBucket::DebugData data = bucket.GetDebugData();
    XCTAssertEqual(data.mPolygonsData.mapSize, 2);
    
    bucket.DeleteBatch(batch1);
    bucket.DeleteBatch(batch2);
    
    data = bucket.GetDebugData();
    XCTAssertEqual(data.mPolygonsData.primitivesCount, bucket.batchSizeLimit()*9);
    XCTAssertEqual(data.mPolygonsData.batchesCount, 9);
    XCTAssertEqual(data.mLinesData.primitivesCount, 0);
    XCTAssertEqual(data.mPolygonsData.primitivesCount, bucket.batchSizeLimit()*9);
    XCTAssertEqual(data.mPolygonsData.mapSize, 1);
    XCTAssertEqual(bucket.batchCount(), 9);
    
    bucket.Clear();
}

- (void)testClear
{
    
}


@end
