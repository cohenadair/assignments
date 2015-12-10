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

Cube *rubiksCube;

double xSpeed, ySpeed, zSpeed;
bool shiftIsDown;

int main (int argc, char **argv);
void onKeyUp(SDL_Keycode key);
void onKeyDown(SDL_Keycode key);
void rotateSide(int faceId);

#endif
