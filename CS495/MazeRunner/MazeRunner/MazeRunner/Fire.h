//
//  Fire.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Fire_h
#define Fire_h

#include "Obstacle.h"

class Fire : public Obstacle {
    
public:
    Fire(Rect *loc);
    void executePlayerFound();
    
};

#endif
