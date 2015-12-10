//
//  constants.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef constants_h
#define constants_h

#define kPi 3.1415926535897932384626433832795

#define kScreenWidth 640
#define kScreenHeight 480
#define kScreenZoom -2.5

#define kNumberOfCubeSides 6
#define kGridSize 3

#define kCubeSize 1.0
#define kCubeRadius kCubeSize / 2

#define kStickerSize kCubeSize / 3
#define kStickerRadius kStickerSize / 2
#define kStickerShrink 0.005
#define kStickerOffset 0.001

#define kFaceFront 0
#define kFaceBack 1
#define kFaceTop 2
#define kFaceBottom 3
#define kFaceLeft 4
#define kFaceRight 5

#define kRotationSpeed 0.15

#define kPieceOffset(mod) mod * kStickerSize

#define kAxisX 0
#define kAxisY 1
#define kAxisZ 2

struct FrontRotationParams {
    int angle;
    float x;
    float y;
    float z;
};

#endif
