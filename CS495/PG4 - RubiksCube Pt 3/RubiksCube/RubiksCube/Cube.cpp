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
    
    // used to "bring side to front" before drawing
    faces[kFaceFront]->setFrontRotationParams(0, 0, 0, 0);
    faces[kFaceBack]->setFrontRotationParams(180, 0, 1, 0);
    faces[kFaceTop]->setFrontRotationParams(-90, 1, 0, 0);
    faces[kFaceBottom]->setFrontRotationParams(90, 1, 0, 0);
    faces[kFaceLeft]->setFrontRotationParams(90, 0, 1, 0);
    faces[kFaceRight]->setFrontRotationParams(-90, 0, 1, 0);
    
    // side rotating animation stuff
    faces[kFaceFront]->setAnimationAxees(kAxisX, kAxisY, kAxisX, kAxisY);
    faces[kFaceBack]->setAnimationAxees(kAxisX, kAxisY, kAxisX, kAxisY);
    faces[kFaceTop]->setAnimationAxees(kAxisY, kAxisY, kAxisY, kAxisY);
    faces[kFaceBottom]->setAnimationAxees(kAxisY, kAxisY, kAxisY, kAxisY);
    faces[kFaceLeft]->setAnimationAxees(kAxisX, kAxisX, kAxisX, kAxisX);
    faces[kFaceRight]->setAnimationAxees(kAxisX, kAxisX, kAxisX, kAxisX);
    
    // some sides pieces need to be rotated in different directions, but on the same angle
    faces[kFaceFront]->setAnimationDirections(-1, -1, 1, 1);
    faces[kFaceBack]->setAnimationDirections(-1, 1, 1, -1);
    faces[kFaceTop]->setAnimationDirections(1, 1, 1, 1);
    faces[kFaceBottom]->setAnimationDirections(-1, -1, -1, -1);
    faces[kFaceLeft]->setAnimationDirections(-1, 1, 1, 1);
    faces[kFaceRight]->setAnimationDirections(-1, -1, 1, -1);
    
    // rotating counterclockwise isn't as simple as "reversing" the clockwise rotation (not sure why)
    faces[kFaceFront]->setAnimationDirectionsCounterclockwise(1, 1, -1, -1);
    faces[kFaceBack]->setAnimationDirectionsCounterclockwise(1, -1, -1, 1);
    faces[kFaceTop]->setAnimationDirectionsCounterclockwise(1, 1, 1, 1);
    faces[kFaceBottom]->setAnimationDirectionsCounterclockwise(-1, -1, -1, -1);
    faces[kFaceLeft]->setAnimationDirectionsCounterclockwise(1, 1, -1, 1);
    faces[kFaceRight]->setAnimationDirectionsCounterclockwise(1, -1, -1, -1);
    
    // initialize rotation variables
    animationAngle = 0;
    xRot = yRot = zRot = 0.0;
    q4.CreateFromAxisAngle(0, 0, 0, 0);
}

// getters and setters
CubeFace ** Cube::getCubeFaces() {
    return faces;
}

void Cube::setXRot(double d) {
    xRot = d;
}

void Cube::setYRot(double d) {
    yRot = d;
}

void Cube::setZRot(double d) {
    zRot = d;
}

// drawing
void Cube::draw() {
    glColor3f(0, 0, 0);
    
    for (int i = 0; i < kNumberOfCubeSides; i++) {
        updateRotation();
        faces[i]->drawStickers(i, animationAngle);
    }
}

// rotation
void Cube::updateRotation() {
    glLoadIdentity();
    glTranslatef(0, 0, kScreenZoom);
    glQuaternion q1, q2, q3;
    q1.CreateFromAxisAngle(1, 0, 0, xRot);
    q2.CreateFromAxisAngle(0, 1, 0, yRot);
    q3.CreateFromAxisAngle(0, 0, 1, zRot);
    GLfloat pm[16];
    q4 = q1 * q2 * q3 * q4;
    q4.Normalize();
    q4.CreateMatrix(pm);
    glMultMatrixf(pm);
}

void Cube::stopRotation() {
    xRot = yRot = zRot = 0;
}

void Cube::rotateClockwise(int face) {
    animationAngle = 90;
    faces[face]->rotateClockwise(face);
}

void Cube::rotateCounterclockwise(int face) {
    animationAngle = -90;
    faces[face]->rotateCounterclockwise(face);
}
