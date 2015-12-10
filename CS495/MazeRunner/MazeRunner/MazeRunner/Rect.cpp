 //
//  Rect.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-04.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Rect.h"

// constructors
Rect::Rect() {
    this->topRight = new Point(0, 0, 0);
    this->topLeft = new Point(0, 0, 0);
    this->bottomRight = new Point(0, 0, 0);
    this->bottomLeft = new Point(0, 0, 0);
}

Rect::Rect(Point *topRight, Point *topLeft, Point *bottomLeft, Point *bottomRight) {
    this->topRight = topRight;
    this->topLeft = topLeft;
    this->bottomLeft = bottomLeft;
    this->bottomRight = bottomRight;
}

Rect::~Rect() {
    delete topRight;
    delete topLeft;
    delete bottomLeft;
    delete bottomRight;
}

// manipulating
Rect * Rect::clone() {
    return new Rect(topRight->clone(), topLeft->clone(), bottomLeft->clone(), bottomRight->clone());
}

bool Rect::intersectsPoint(Point *p, float tolerance) {
    double xMin = topLeft->getX() - tolerance;
    double xMax = topRight->getX() + tolerance;
    double yMin = bottomLeft->getY() - tolerance;
    double yMax = topLeft->getY() + tolerance;
    double zMin = topRight->getZ() - tolerance;
    double zMax = topLeft->getZ() + tolerance;
    
    // this should always pring "1"s for every case
    //cout << "X: " << (xMin <= xMax) << ", Y: " << (yMin <= yMax) << ", Z: " << (zMin <= zMax) << endl;
    
    return xMin <= p->getX() && xMax >= p->getX() && yMin <= p->getY() && yMax >= p->getY() && zMin <= p->getZ() && zMax >= p->getZ();
}

// getters and setters
Point * Rect::getTopRight() {
    return topRight;
}

void Rect::setTopRight(Point *p) {
    topRight = p;
}

Point * Rect::getTopLeft() {
    return topLeft;
}

void Rect::setTopLeft(Point *p) {
    topLeft = p;
}

Point * Rect::getBottomLeft() {
    return bottomLeft;
}

void Rect::setBottomLeft(Point *p) {
    bottomLeft = p;
}

Point * Rect::getBottomRight() {
    return bottomRight;
}

void Rect::setBottomRight(Point *p) {
    bottomRight = p;
}

float Rect::getLength() {
    return length;
}

void Rect::setLength(float len) {
    length = len;
}

// drawing
void Rect::draw() {
    glBegin(GL_QUADS);
        bottomLeft->draw();
        bottomRight->draw();
        topRight->draw();
        topLeft->draw();
    glEnd();
}

// draws the rectangle with the specified texture; repeats the texture the specified amount of times
void Rect::draw(int textureIndex, int repeatX, int repeatY) {
    GLUtils::switchTexture(textureIndex);
    
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        bottomLeft->draw();
    
        glTexCoord2f(repeatX, 0);
        bottomRight->draw();
    
        glTexCoord2f(repeatX, repeatY);
        topRight->draw();
    
        glTexCoord2f(0, repeatY);
        topLeft->draw();
    glEnd();
}

void Rect::draw2D(int textureIndex) {
    GLUtils::switchTexture(textureIndex);
    
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1);
        bottomLeft->draw2D();

        glTexCoord2f(1, 1);
        bottomRight->draw2D();

        glTexCoord2f(1, 0);
        topRight->draw2D();
    
        glTexCoord2f(0, 0);
        topLeft->draw2D();
    glEnd();
}

// debugging
void Rect::print() {
    topRight->print();
    topLeft->print();
    bottomLeft->print();
    bottomRight->print();
}


