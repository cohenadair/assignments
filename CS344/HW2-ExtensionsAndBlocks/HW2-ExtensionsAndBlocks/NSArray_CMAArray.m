//
//  NSArray_CMAArray.m
//  HW2-ExtensionsAndBlocks
//
//  Created by Cohen Adair on 10/27/14.
//  Copyright (c) 2014 Cohen Adair. All rights reserved.
//

#import "NSArray_CMAArray.h"

@implementation NSArray (CMAArray)

// return an array with results of invoking collectBlock on each item in the collection
- (NSArray *)collect: (enumBlock)collectBlock {
    NSMutableArray *result = [NSMutableArray array];
    
    for (id obj in self)
        [result addObject:collectBlock(obj)];
    
    return result;
}

// return an array with each item for whic hselectBlock retured YES
- (NSArray *)select: (selBlock)selectBlock {
    NSMutableArray *result = [NSMutableArray array];
    
    for (id obj in self)
        if (selectBlock(obj))
            [result addObject:obj];
    
    return result;
}

// return an array with each item for which select block returned NO
- (NSArray *)reject: (selBlock)rejectBlock {
    NSMutableArray *result = [NSMutableArray array];
    
    for (id obj in self)
        if (!rejectBlock(obj))
            [result addObject:obj];
    
    return result;
}

@end