//
//  ScoreBoost.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef ScoreBoost_h
#define ScoreBoost_h

#include "Obstacle.h"

class ScoreBoost : public Obstacle {

public:
    ScoreBoost(Rect *loc);
    void executePlayerFound();
    
};

#endif
