//
//  SpeedBoost.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "SpeedBoost.h"

SpeedBoost::SpeedBoost(Rect *loc) : Obstacle(loc, kTextureSpeedBoost) {
    
}

void SpeedBoost::executePlayerFound() {
    if (isFound())
        return;
    
    Game::setSpeed(0.30);
    Game::incScoreBy(1000);
    
    setFound(true);
}