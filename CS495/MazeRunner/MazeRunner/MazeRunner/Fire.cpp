//
//  Fire.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Fire.h"

Fire::Fire(Rect *loc) : Obstacle(loc, kTextureFire) {
    
}

void Fire::executePlayerFound() {
    if (Game::didHitFire())
        return;
    
    Game::incScoreBy(-2500);
    Game::setHitFire(true);
}
