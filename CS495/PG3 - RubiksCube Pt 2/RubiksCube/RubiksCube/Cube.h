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
    double xRot, yRot, zRot;
    
    // initializing
    void init();
    
public:
    // constructors
    Cube();
    ~Cube();
    
    // getters and setters
    CubeFace ** getCubeFaces();
    void incXRot(double d);
    void incYRot(double d);
    void incZRot(double d);
    
    // drawing
    void draw();
    
    // rotations
    void rotateClockwise(int face);
    void rotateCounterclockwise(int face);
    
    // debugging
    void debugSides();
};

#endif
