 //
//  Square.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-04.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Square.h"

// constructors
Square::Square() {
    this->topRight = new Point(0, 0, 0);
    this->topLeft = new Point(0, 0, 0);
    this->bottomRight = new Point(0, 0, 0);
    this->bottomLeft = new Point(0, 0, 0);
}

Square::Square(Point *topRight, Point *topLeft, Point *bottomLeft, Point *bottomRight) {
    this->topRight = topRight;
    this->topLeft = topLeft;
    this->bottomLeft = bottomLeft;
    this->bottomRight = bottomRight;
}

Square::~Square() {
    delete topRight;
    delete topLeft;
    delete bottomLeft;
    delete bottomRight;
}

// manipulating
Square * Square::clone() {
    return new Square(topRight->clone(), topLeft->clone(), bottomLeft->clone(), bottomRight->clone());
}

// getters and setters
Point * Square::getTopRight() {
    return topRight;
}

void Square::setTopRight(Point *p) {
    topRight = p;
}

Point * Square::getTopLeft() {
    return topLeft;
}

void Square::setTopLeft(Point *p) {
    topLeft = p;
}

Point * Square::getBottomLeft() {
    return bottomLeft;
}

void Square::setBottomLeft(Point *p) {
    bottomLeft = p;
}

Point * Square::getBottomRight() {
    return bottomRight;
}

void Square::setBottomRight(Point *p) {
    bottomRight = p;
}

// drawing
void Square::draw() {
    glBegin(GL_QUADS);
    
    bottomLeft->draw();
    bottomRight->draw();
    topRight->draw();
    topLeft->draw();
    
    glEnd ();
}


