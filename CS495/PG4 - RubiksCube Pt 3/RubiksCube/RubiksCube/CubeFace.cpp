//
//  CubeFace.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "CubeFace.h"

// constructors
CubeFace::CubeFace() {
    
}

CubeFace::CubeFace(int textureIndex, int rotationAxis) {
    this->textureIndex = textureIndex;
    this->rotationAxis = rotationAxis;
    init();
}

CubeFace::~CubeFace() {
    delete sideFaces;
    
    for (int i = 0; i < kGridSize; i++) {
        for (int j = 0; j < kGridSize; j++)
            delete stickers[i][j];
        delete stickers[i];
    }
    delete stickers;
}

// initializing
void CubeFace::init() {
    // initialize vector sizes
    stickers = new Sticker**[kGridSize];
    for (int i = 0; i < kGridSize; i++)
        stickers[i] = new Sticker*[kGridSize];

    for (int r = 0; r < kGridSize; r++)
        for (int c = 0; c < kGridSize; c++)
            stickers[r][c] = new Sticker(textureIndex, r, c);
    
    setFrontRotationParams(0, 0, 0, 0);
}

// getters and setters
Sticker *** CubeFace::getStickers() {
    return stickers;
}

void CubeFace::setFaces(CubeFace *north, CubeFace *east, CubeFace *south, CubeFace *west) {
    sideFaces = new CubeFace *[4];
    sideFaces[kWestFace] = west;
    sideFaces[kNorthFace] = north;
    sideFaces[kEastFace] = east;
    sideFaces[kSouthFace] = south;
}

void CubeFace::setFrontRotationParams(int angle, float x, float y, float z) {
    frontRotationParams.angle = angle;
    frontRotationParams.x = x;
    frontRotationParams.y = y;
    frontRotationParams.z = z;
}

void CubeFace::setAnimationAxees(int north, int east, int south, int west) {
    animationAxees[kNorthFace] = north;
    animationAxees[kEastFace] = east;
    animationAxees[kSouthFace] = south;
    animationAxees[kWestFace] = west;
}

void CubeFace::setAnimationDirections(int north, int east, int south, int west) {
    animationDirections[kNorthFace] = north;
    animationDirections[kEastFace] = east;
    animationDirections[kSouthFace] = south;
    animationDirections[kWestFace] = west;
}

void CubeFace::setAnimationDirectionsCounterclockwise(int north, int east, int south, int west) {
    animationDirectionsCounterclockwise[kNorthFace] = north;
    animationDirectionsCounterclockwise[kEastFace] = east;
    animationDirectionsCounterclockwise[kSouthFace] = south;
    animationDirectionsCounterclockwise[kWestFace] = west;
}

// rotation
void CubeFace::rotateClockwise(int faceId) {
    rotate(faceId, -90);
}

void CubeFace::rotateCounterclockwise(int faceId) {
    rotate(faceId, 90);
}

void CubeFace::rotate(int faceId, int angle) {
    // setup stickers for rotate
    for (int i = 0; i < kGridSize; i++)
        for (int j = 0; j < kGridSize; j++)
            stickers[i][j]->rotate(angle, kAxisZ, 1);
    
    // rotate face stickers (same for every face)
    if (!clockwise(angle)) {
        swap(stickers[0][0], stickers[2][0]);
        swap(stickers[0][0], stickers[2][2]);
        swap(stickers[0][0], stickers[0][2]);
        
        swap(stickers[0][1], stickers[1][0]);
        swap(stickers[0][1], stickers[2][1]);
        swap(stickers[0][1], stickers[1][2]);
    } else {
        swap(stickers[0][0], stickers[0][2]);
        swap(stickers[0][0], stickers[2][2]);
        swap(stickers[0][0], stickers[2][0]);
        
        swap(stickers[0][1], stickers[1][2]);
        swap(stickers[0][1], stickers[2][1]);
        swap(stickers[0][1], stickers[1][0]);
    }
    
    // rotate side stickers
    rotateSides(faceId, angle);
}

void CubeFace::rotateSides(int faceId, int angle) {
    switch (faceId) {
        case kFaceFront: {
            int arr[][3][2] = {
                {{2, 0}, {1, 0}, {0, 0}}, // west
                {{2, 2}, {2, 1}, {2, 0}}, // north
                {{0, 2}, {1, 2}, {2, 2}}, // east
                {{0, 0}, {0, 1}, {0, 2}}  // south
            };
            int angles[] = {
                -90, // west
                -90, // north
                -90, // east
                -90  // south
            };
            rotateSidesHelper(arr, angle, angles);
            break;
        }
            
        case kFaceTop: {
            int arr[][3][2] = {
                {{0, 0}, {0, 1}, {0, 2}}, // west
                {{0, 0}, {0, 1}, {0, 2}}, // north
                {{0, 0}, {0, 1}, {0, 2}}, // east
                {{0, 0}, {0, 1}, {0, 2}}  // south
            };
            int angles[] = {
                0, // west
                0, // north
                0, // east
                0  // south
            };
            rotateSidesHelper(arr, angle, angles);
            break;
        }
            
        case kFaceLeft: {
            int arr[][3][2] = {
                {{2, 0}, {1, 0}, {0, 0}}, // west
                {{0, 2}, {1, 2}, {2, 2}}, // north
                {{0, 2}, {1, 2}, {2, 2}}, // east
                {{0, 2}, {1, 2}, {2, 2}}  // south
            };
            int angles[] = {
                180, // west
                (180 * clockwise(angle)), // north
                0, // east
                (180 * !clockwise(angle))  // south
            };
            rotateSidesHelper(arr, angle, angles);
            break;
        }
            
        case kFaceRight: {
            int arr[][3][2] = {
                {{2, 0}, {1, 0}, {0, 0}}, // west
                {{2, 0}, {1, 0}, {0, 0}}, // north
                {{0, 2}, {1, 2}, {2, 2}}, // east
                {{2, 0}, {1, 0}, {0, 0}}  // south
            };
            int angles[] = {
                0, // west
                (180 * !clockwise(angle)), // north
                180, // east
                (180 * clockwise(angle))  // south
            };
            rotateSidesHelper(arr, angle, angles);
            break;
        }
            
        case kFaceBack: {
            int arr[][3][2] = {
                {{2, 0}, {1, 0}, {0, 0}}, // west
                {{0, 0}, {0, 1}, {0, 2}}, // north
                {{0, 2}, {1, 2}, {2, 2}}, // east
                {{2, 2}, {2, 1}, {2, 0}}  // south
            };
            int angles[] = {
                90, // west
                90, // north
                90, // east
                90  // south
            };
            rotateSidesHelper(arr, angle, angles);
            break;
        }
            
        case kFaceBottom: {
            int arr[][3][2] = {
                {{2, 2}, {2, 1}, {2, 0}}, // west
                {{2, 2}, {2, 1}, {2, 0}}, // north
                {{2, 2}, {2, 1}, {2, 0}}, // east
                {{2, 2}, {2, 1}, {2, 0}}  // south
            };
            int angles[] = {
                0, // west
                0, // north
                0, // east
                0  // south
            };
            rotateSidesHelper(arr, angle, angles);
            break;
        }
            
        default:
            break;
    }
}

// rotates the side stickers
void CubeFace::rotateSidesHelper(int p[][3][2], int angle, int orientationAngles[]) {
    for (int i = 0; i < 4; i++) {
        if (!clockwise(angle))
            orientationAngles[i] *= -1;
        
        for (int j = 0; j < kGridSize; j++)
            sideFaces[i]->getStickers()[p[i][j][0]][p[i][j][1]]->rotate(orientationAngles[i], animationAxees[i], clockwise(angle) ? animationDirections[i] : animationDirectionsCounterclockwise[i]);
    }
    
    if (!clockwise(angle))
        swapWestNorth(p);
    else
        swapWestSouth(p);
    
    swapWestEast(p);
    
    if (!clockwise(angle))
        swapWestSouth(p);
    else
        swapWestNorth(p);
}

void CubeFace::swapWestNorth(int p[][3][2]) {
    for (int i = 0; i < kGridSize; i++) {
        swap(sideFaces[kWestFace]->getStickers()[p[kWestFace][i][0]][p[kWestFace][i][1]],
             sideFaces[kNorthFace]->getStickers()[p[kNorthFace][i][0]][p[kNorthFace][i][1]]);
    }
}

void CubeFace::swapWestEast(int p[][3][2]) {
    for (int i = 0; i < kGridSize; i++) {
        swap(sideFaces[kWestFace]->getStickers()[p[kWestFace][i][0]][p[kWestFace][i][1]],
             sideFaces[kEastFace]->getStickers()[p[kEastFace][i][0]][p[kEastFace][i][1]]);
    }
}

void CubeFace::swapWestSouth(int p[][3][2]) {
    for (int i = 0; i < kGridSize; i++) {
        swap(sideFaces[kWestFace]->getStickers()[p[kWestFace][i][0]][p[kWestFace][i][1]],
             sideFaces[kSouthFace]->getStickers()[p[kSouthFace][i][0]][p[kSouthFace][i][1]]);
    }
}

bool CubeFace::clockwise(int angle) {
    return (angle < 0);
}

// drawing
void CubeFace::faceFront() {
    glRotatef(frontRotationParams.angle, frontRotationParams.x, frontRotationParams.y, frontRotationParams.z);
}

// draws all the stickers
void CubeFace::drawStickers(int faceIndex, double &animationAngle) {
    faceFront();
    for (int r = 0; r < kGridSize; r++)
        for (int c = 0; c < kGridSize; c++)
            stickers[r][c]->draw(r, c, animationAngle);
    
    if (animationAngle != 0)
        animationAngle += (animationAngle > 0) ? -0.75 : 0.75;
}
