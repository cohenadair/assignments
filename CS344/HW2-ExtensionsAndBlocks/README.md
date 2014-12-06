Homework 2 - Extensions and Blocks
==================================

1. Declare an extension to the NSArray and NSSet classes.
2. Declare the types:
```objective-c
enumBlock // a block that takes an object of type id, and returns type id
selBlock  // a block that takes an object of type id, and returns type BOOL
```

3. Each class should implement these methods:
```objective-c
// return an array with results of invoking collectBlock
// on each item in collection.
- (NSArray *)collect: (enumBlock)collectBlock;

// return an array with each item for which selectBlock
// returned YES.
- (NSArray *)select: (selBlock)selectBlock;

// return an array with each item for which selectBlock
// returned NO.
- (NSArray *)reject: (selBlock)rejectBlock;
```

4. Implement the above methods with NSArray replaced by NSSet.