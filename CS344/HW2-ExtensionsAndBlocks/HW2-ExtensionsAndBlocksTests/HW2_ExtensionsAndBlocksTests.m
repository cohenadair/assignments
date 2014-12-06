//
//  HW2_ExtensionsAndBlocksTests.m
//  HW2-ExtensionsAndBlocksTests
//
//  Created by Cohen Adair on 10/27/14.
//  Copyright (c) 2014 Cohen Adair. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>
#import "NSSet_CMASet.h"
#import "NSArray_CMAArray.h"

@interface HW2_ExtensionsAndBlocksTests : XCTestCase

@end

@implementation HW2_ExtensionsAndBlocksTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testCollectSelectReject {
    enumBlock squareBlock = ^(id obj) {
        NSNumber *result = [NSNumber numberWithLong:[obj integerValue] * [obj integerValue]];
        return result;
    };
    
    selBlock greaterThanZeroBlock = ^(id obj) {
        BOOL result = ([obj integerValue] > 0);
        return result;
    };
    
    NSArray *anArray = @[@1, @-2, @3, @4, @-5, @6];
    NSSet *aSet = [NSSet setWithObjects:@5, @-6, @-7, @10, @9, @3, nil];
    
    NSArray *squaredArray = [anArray collect:squareBlock];
    BOOL assert = [squaredArray isEqualToArray:[NSArray arrayWithObjects:@1, @4, @9, @16, @25, @36, nil]];
    XCTAssert(assert);
    
    NSArray *greaterThanZeroArray = [anArray select:greaterThanZeroBlock];
    assert = [greaterThanZeroArray isEqualToArray:[NSArray arrayWithObjects:@1, @3, @4, @6, nil]];
    XCTAssert(assert);
    
    NSArray *lessThanZeroArray = [anArray reject:greaterThanZeroBlock];
    assert = [lessThanZeroArray isEqualToArray:[NSArray arrayWithObjects:@-2, @-5, nil]];
    XCTAssert(assert);
    
    NSSet *squaredSet = [aSet collect:squareBlock];
    assert = [squaredSet isEqualToSet:[NSSet setWithObjects:@25, @36, @49, @100, @81, @9, nil]];
    XCTAssert(assert);
    
    NSSet *greaterThanZeroSet = [aSet select:greaterThanZeroBlock];
    assert = [greaterThanZeroSet isEqualToSet:[NSSet setWithObjects:@5, @10, @9, @3, nil]];
    XCTAssert(assert);
    
    NSSet *lessThanZeroSet = [aSet reject:greaterThanZeroBlock];
    assert = [lessThanZeroSet isEqualToSet:[NSSet setWithObjects:@-6, @-7, nil]];
    XCTAssert(assert);
}

@end
