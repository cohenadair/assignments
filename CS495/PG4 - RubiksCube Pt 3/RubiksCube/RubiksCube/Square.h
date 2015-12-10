//
//  Square.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-04.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Square_h
#define Square_h

#include "Point.h"

class Square {
    
private:
    // vertices
    Point *topRight;
    Point *topLeft;
    Point *bottomLeft;
    Point *bottomRight;
    
public:
    // constructors
    Square();
    Square(Point *topRight, Point *topLeft, Point *bottomLeft, Point *bottomRight);
    ~Square();
    
    // manipulating
    Square * clone();
    
    // getters and setters
    Point * getTopRight();
    void setTopRight(Point *p);
    Point * getTopLeft();
    void setTopLeft(Point *p);
    Point * getBottomLeft();
    void setBottomLeft(Point *p);
    Point * getBottomRight();
    void setBottomRight(Point *p);
    
    // drawing
    void draw();
    
};

#endif
