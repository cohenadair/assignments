//
//  BlackHole.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef BlackHole_h
#define BlackHole_h

#include "Obstacle.h"

class BlackHole : public Obstacle {
    
public:
    BlackHole(Rect *loc);
    void executePlayerFound();
    
};

#endif
