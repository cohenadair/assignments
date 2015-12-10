//
//  Obstacle.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Obstacle_h
#define Obstacle_h

#include "Rect.h"

class Obstacle {
    
private:
    Rect *location;
    int textureIntex;
    bool isTrap;
    bool found;
    
    
public:
    Obstacle(Rect *loc, int texture);
    virtual ~Obstacle();
    
    virtual void executePlayerFound() = 0;
    
    bool intersectsPoint(Point *p);
    bool isFound();
    void setFound(bool b);
    void draw();
};


#endif
