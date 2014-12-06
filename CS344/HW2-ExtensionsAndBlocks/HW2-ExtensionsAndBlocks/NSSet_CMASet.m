//
//  NSSet_CMASet.m
//  HW2-ExtensionsAndBlocks
//
//  Created by Cohen Adair on 10/27/14.
//  Copyright (c) 2014 Cohen Adair. All rights reserved.
//

#import "NSSet_CMASet.h"

@implementation NSSet (CMASet)

// return an array with results of invoking collectBlock on each item in the collection
- (NSSet *)collect: (enumBlock)collectBlock {
    NSMutableSet *result = [NSMutableSet set];
    
    for (id obj in self)
        [result addObject:collectBlock(obj)];
    
    return result;
}

// return an array with each item for whic hselectBlock retured YES
- (NSSet *)select: (selBlock)selectBlock {
    NSMutableSet *result = [NSMutableSet set];
    
    for (id obj in self)
        if (selectBlock(obj))
            [result addObject:obj];
    
    return result;
}

// return an array with each item for which select block returned NO
- (NSSet *)reject: (selBlock)rejectBlock {
    NSMutableSet *result = [NSMutableSet set];
    
    for (id obj in self)
        if (!rejectBlock(obj))
            [result addObject:obj];
    
    return result;
}

@end
