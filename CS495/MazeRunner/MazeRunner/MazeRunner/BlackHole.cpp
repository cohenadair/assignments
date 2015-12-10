//
//  BlackHole.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "BlackHole.h"

BlackHole::BlackHole(Rect *loc) : Obstacle(loc, kTextureBlackHole) {
    
}

void BlackHole::executePlayerFound() {
    Game::setHitBlackHole(true);
    Game::incScoreBy(-2500);
}
