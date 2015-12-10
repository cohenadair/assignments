//
//  Point.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Point_h
#define Point_h

#include <string>
#include "GLUtils.h"

class Point {
    
private:
    double x;
    double y;
    double z;
    
public:
    // constructors
    Point(double x, double y, double z);
    Point(double x, double y);
    
    // getters and setters
    double getX();
    void setX(double d);
    double getY();
    void setY(double d);
    double getZ();
    void setZ(double d);
    
    // drawing
    void draw();
    
    // manipulating
    Point * clone();
    
};

#endif
