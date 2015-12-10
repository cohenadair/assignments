//
//  main.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-09-23.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef main_h
#define main_h

#include <iostream>
#include "Cube.h"
using namespace std;

Cube *rubixCube;

double xSpeed, ySpeed, zSpeed;
bool rotating, shiftIsDown;

int main (int argc, char **argv);
void onKeyUp(SDL_Keycode key);
void onKeyPress(SDL_Keycode key);
void rotateSide(int faceId, bool clockwise);

#endif
