//
//  Rect.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-04.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Rect_h
#define Rect_h

#include "Point.h"

class Rect {
    
private:
    // vertices
    Point *topRight;
    Point *topLeft;
    Point *bottomLeft;
    Point *bottomRight;
    
    float length;
    
public:
    // constructors
    Rect();
    Rect(Point *topRight, Point *topLeft, Point *bottomLeft, Point *bottomRight);
    ~Rect();
    
    // manipulating
    Rect * clone();
    bool intersectsPoint(Point *p, float tolerance);
    
    // getters and setters
    Point * getTopRight();
    void setTopRight(Point *p);
    Point * getTopLeft();
    void setTopLeft(Point *p);
    Point * getBottomLeft();
    void setBottomLeft(Point *p);
    Point * getBottomRight();
    void setBottomRight(Point *p);
    float getLength();
    void setLength(float len);
    
    // drawing
    void draw();
    void draw(int textureIndex, int repeatX, int repeatY);
    void draw2D(int textureIndex);
    
    // debugging
    void print();
    
};

#endif
