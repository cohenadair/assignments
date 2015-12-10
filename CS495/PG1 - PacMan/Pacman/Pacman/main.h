//
//  main.h
//  Pacman
//
//  Created by Cohen Adair on 2015-08-31.
//  Copyright (c) 2015 Cohen Adair. All rights reserved.
//

#ifndef Pacman_main_h
#define Pacman_main_h

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
using namespace std;

// screen dimensions
#define kScreenX 0
#define kScreenY 0
#define kScreenW 640
#define kScreenH 480

// indexes of pacmanImages
#define kUp 0
#define kRight 1
#define kDown 2
#define kLeft 3

// index of pacmanImages[i]
#define kClosed 0
#define kOpened 1

#define kNumberOfDirections 4
#define kNumberOfVariations 2

SDL_Window *window;
SDL_Surface *surface;

double pacmanX, pacmanY, pacmanW, pacmanH;
double foodX, foodY, foodW, foodH;

int currentDirection;
int currentVariation;

vector<vector<SDL_Surface *>> pacmanImages;
SDL_Surface *foodImage;

Mix_Chunk *chompSound;
Mix_Chunk *sirenSound;

void init();
void close();
void draw();
void redraw();
void move();

Uint32 toggleMouthCallback(Uint32 interval, void *param);

void onKeyPress(SDL_Keycode key);
bool isOnEdge();
void attemptToEat();
void relocateFood();
SDL_Rect * newRect(int x, int y, int w, int h);
double distanceBetweenPoints(int x1, int y1, int x2, int y2);

#endif
