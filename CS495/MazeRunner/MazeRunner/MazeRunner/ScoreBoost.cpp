//
//  ScoreBoost.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "ScoreBoost.h"

ScoreBoost::ScoreBoost(Rect *loc) : Obstacle(loc, kTextureScoreBoost) {
    
}

void ScoreBoost::executePlayerFound() {
    if (isFound())
        return;
    
    Game::incScoreBy(5000);
    
    setFound(true);
}