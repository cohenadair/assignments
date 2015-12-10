//
//  Point.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Point.h"

// constructors
Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point::Point(double x, double y) {
    this->x = x;
    this->y = y;
    z = 0;
}

// getters and setters
double Point::getX() {
    return x;
}

void Point::setX(double d) {
    x = d;
}

double Point::getY() {
    return y;
}

void Point::setY(double d) {
    y = d;
}

double Point::getZ() {
    return z;
}

void Point::setZ(double d) {
    z = d;
}

// drawing
void Point::draw() {
    glVertex3f(x, y, z);
}

// manipulating
Point * Point::clone() {
    return new Point(x, y, z);
}

