//
//  SpeedBoost.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef SpeedBoost_h
#define SpeedBoost_h

#include "Obstacle.h"

class SpeedBoost : public Obstacle {
    
public:
    SpeedBoost(Rect *loc);
    void executePlayerFound();
    
};

#endif
