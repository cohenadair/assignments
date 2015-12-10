//
//  Obstacle.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-26.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Obstacle.h"

Obstacle::Obstacle(Rect *loc, int texture) {
    location = loc;
    textureIntex = texture;
    found = false;
}

Obstacle::~Obstacle() {
    delete location;
}

bool Obstacle::intersectsPoint(Point *p) {
    return location->intersectsPoint(p, 0.5);
}

bool Obstacle::isFound() {
    return found;
}

void Obstacle::setFound(bool b) {
    found = b;
}

void Obstacle::draw() {
    if (!found)
        location->draw(textureIntex, 1, 1);
}
