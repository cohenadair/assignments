//
//  main.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-09-23.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef main_h
#define main_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;

#define PI 3.1415926535897932384626433832795

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_ZOOM -2.5
#define CUBE_RADIUS 0.5
#define CUBE_SIZE 1.0
#define CUBE_OFFSET 0.5001
#define SM_SQ_SIZE (CUBE_RADIUS * 2) / 3
#define SM_SQ_SHRINK 0.005;
#define ROTATION_SPEED 0.5;

SDL_Window *w;

SDL_Surface **TI;

GLuint *texture;

double xRot, yRot, zRot, xSpeed, ySpeed, zSpeed;
bool rotating;

struct Point {
    double x;
    double y;
    double z;
};

struct Square {
    Point topRight;
    Point topLeft;
    Point bottomLeft;
    Point bottomRight;
};

typedef Point (*PieceFunction)(Point, int, int);

int main (int argc, char **argv);
void initOGL();
void initTextures();
void release();
void predraw() ;
void drawSquare(Square sq);
void draw9Squares(Square smBaseSq, PieceFunction pFunc);
void draw9SquaresZ(Square bigSq);
void draw9SquaresX(Square bigSq);
void draw9SquaresY(Square bigSq);
void drawPoint3f(Point p);
Point zPiecePoint(Point base, int row, int col);
Point xPiecePoint(Point base, int row, int col);
Point yPiecePoint(Point base, int row, int col);
double pieceOffset(int modifier);
Square zSquare(double z);
Square xSquare(double x);
Square ySquare(double y);
void switchTexture(int index);
void onKeyPress(SDL_Keycode key);
void resetRotationVariables();

Point newPoint(double x, double y, double z);
Square newSquare(Point topRight, Point topLeft, Point bottomLeft, Point bottomRight);

#endif
