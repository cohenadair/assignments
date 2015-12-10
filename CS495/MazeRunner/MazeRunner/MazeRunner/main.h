//
//  main.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef main_h
#define main_h

#include "Maze.h"
#include "Player.h"
#include "Hud.h"
#include "Game.h"

Player *player;
Maze *currentMaze;
Hud *hud;
bool quit;

void restart();
void goToTextLevel();
void onKeyDown(SDL_Keycode key);

#endif
