//
//  NSSet_CMASet.h
//  HW2-ExtensionsAndBlocks
//
//  Created by Cohen Adair on 10/27/14.
//  Copyright (c) 2014 Cohen Adair. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface NSSet (CMASet)

typedef id (^enumBlock)(id);
typedef BOOL (^selBlock)(id);

// return an array with results of invoking collectBlock on each item in the collection
- (NSSet *)collect: (enumBlock)collectBlock;

// return an array with each item for whic hselectBlock retured YES
- (NSSet *)select: (selBlock)selectBlock;

// return an array with each item for which select block returned NO
- (NSSet *)reject: (selBlock)rejectBlock;

@end
