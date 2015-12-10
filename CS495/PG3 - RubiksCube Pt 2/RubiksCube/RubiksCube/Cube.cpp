//
//  Cube.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Cube.h"

// constructors
Cube::Cube() {
    init();
}

Cube::~Cube() {
    for (int i = 0; i < kNumberOfCubeSides; i++)
        delete faces[i];
    delete faces;
}

// initializing
void Cube::init() {
    faces = new CubeFace *[kNumberOfCubeSides];
    
    // initialize the each face of the cube with their rotation axis
    faces[kFaceFront] = new CubeFace(kFaceFront, kAxisZ);
    faces[kFaceBack] = new CubeFace(kFaceBack, kAxisZ);
    faces[kFaceTop] = new CubeFace(kFaceTop, kAxisY);
    faces[kFaceBottom] = new CubeFace(kFaceBottom, kAxisY);
    faces[kFaceLeft] = new CubeFace(kFaceLeft, kAxisX);
    faces[kFaceRight] = new CubeFace(kFaceRight, kAxisX);
    
    // initialize each face's neighbors for rotations
    faces[kFaceFront]->setFaces(faces[kFaceTop], faces[kFaceRight], faces[kFaceBottom], faces[kFaceLeft]);
    faces[kFaceBack]->setFaces(faces[kFaceTop], faces[kFaceLeft], faces[kFaceBottom], faces[kFaceRight]);
    faces[kFaceTop]->setFaces(faces[kFaceBack], faces[kFaceRight], faces[kFaceFront], faces[kFaceLeft]);
    faces[kFaceBottom]->setFaces(faces[kFaceFront], faces[kFaceRight], faces[kFaceBack], faces[kFaceLeft]);
    faces[kFaceLeft]->setFaces(faces[kFaceTop], faces[kFaceFront], faces[kFaceBottom], faces[kFaceBack]);
    faces[kFaceRight]->setFaces(faces[kFaceTop], faces[kFaceBack], faces[kFaceBottom], faces[kFaceFront]);
    
    faces[kFaceFront]->setFrontRotationParams(0, 0, 0, 0);
    faces[kFaceBack]->setFrontRotationParams(180, 0, 1, 0);
    faces[kFaceTop]->setFrontRotationParams(-90, 1, 0, 0);
    faces[kFaceBottom]->setFrontRotationParams(90, 1, 0, 0);
    faces[kFaceLeft]->setFrontRotationParams(90, 0, 1, 0);
    faces[kFaceRight]->setFrontRotationParams(-90, 0, 1, 0);
    
    // initialize rotation variables
    xRot = yRot = zRot = 0.0;
}

// getters and setters
CubeFace ** Cube::getCubeFaces() {
    return faces;
}

void Cube::incXRot(double d) {
    xRot += d;
}

void Cube::incYRot(double d) {
    yRot += d;
}

void Cube::incZRot(double d) {
    zRot += d;
}

// drawing
void Cube::draw() {
    for (int i = 0; i < kNumberOfCubeSides; i++) {
        faces[i]->drawBackdrop(xRot, yRot, zRot);
        faces[i]->drawStickers(i);
    }
}

void Cube::rotateClockwise(int face) {
    faces[face]->rotateClockwise(face);
}

void Cube::rotateCounterclockwise(int face) {
    faces[face]->rotateCounterclockwise(face);
}
