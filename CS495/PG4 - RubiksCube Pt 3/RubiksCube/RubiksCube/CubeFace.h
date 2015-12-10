//
//  CubeFace.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef CubeFace_hpp
#define CubeFace_hpp

#include <iostream>
#include "Sticker.h"
using namespace std;

#define kWestFace 0
#define kNorthFace 1
#define kEastFace 2
#define kSouthFace 3
#define kNumberOfFaces 4

class CubeFace {
    
private:
    // for texture accessing
    double textureIndex;
    
    // for rotations
    FrontRotationParams frontRotationParams;
    int animationAxees[kNumberOfFaces];
    int animationDirections[kNumberOfFaces];
    int animationDirectionsCounterclockwise[kNumberOfFaces];
    int rotationAxis;
    
    // grid of face image
    Sticker ***stickers;
    
    // references to other faces for rotation
    CubeFace **sideFaces;
    
    // initializing
    void init();
    
    // drawing
    void drawGrid(double xRot, double yRot, double zRot);
    
    // rotation
    void rotate(int faceId, int angle);
    void rotateSides(int faceId, int angle);
    void rotateSidesHelper(int p[][3][2], int angle, int orientationAngles[]);
    void swapWestNorth(int p[][3][2]);
    void swapWestEast(int p[][3][2]);
    void swapWestSouth(int p[][3][2]);
    bool clockwise(int angle);
    
public:
    // constructors
    CubeFace();
    CubeFace(int textureIndex, int rotationAxis);
    ~CubeFace();
    
    // getters and setters
    Sticker *** getStickers();
    void setFaces(CubeFace *north, CubeFace *east, CubeFace *south, CubeFace *west);
    void setFrontRotationParams(int angle, float x, float y, float z);
    void setAnimationAxees(int north, int east, int south, int west);
    void setAnimationDirections(int north, int east, int south, int west);
    void setAnimationDirectionsCounterclockwise(int north, int east, int south, int west);

    // rotation
    void rotateClockwise(int faceId);
    void rotateCounterclockwise(int faceId);
    
    // drawing
    void faceFront();
    void drawStickers(int faceIndex, double &animationAngle);
    
};

#endif 
