//
//  Cube.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Cube_h
#define Cube_h

#include "CubeFace.h"
using namespace std;

class Cube {
    
private:
    CubeFace **faces;
    
    // rotation variables
    double animationAngle;
    double xRot, yRot, zRot;
    glQuaternion q4;
    
    // initializing
    void init();
    
    // rotation
    void updateRotation();
    
public:
    // constructors
    Cube();
    ~Cube();
    
    // getters and setters
    CubeFace ** getCubeFaces();
    void setXRot(double d);
    void setYRot(double d);
    void setZRot(double d);
    
    // drawing
    void draw();
    
    // rotations
    void stopRotation();
    void rotateClockwise(int face);
    void rotateCounterclockwise(int face);
    
    // debugging
    void debugSides();
};

#endif
