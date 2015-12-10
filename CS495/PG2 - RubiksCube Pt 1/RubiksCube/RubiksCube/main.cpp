//
//  main.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-09-23.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "main.h"

int main(int argc, char **argv) {
    initOGL();
    initTextures();

    resetRotationVariables();
    rotating = false;
    SDL_Event event;

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            
            if (event.type == SDL_KEYDOWN)
                onKeyPress(event.key.keysym.sym);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        drawSquare(zSquare(-CUBE_RADIUS)); switchTexture(0); draw9SquaresZ(zSquare(-CUBE_OFFSET));
        drawSquare(zSquare(CUBE_RADIUS));  switchTexture(1); draw9SquaresZ(zSquare(CUBE_OFFSET));
        drawSquare(xSquare(-CUBE_RADIUS)); switchTexture(2); draw9SquaresX(xSquare(-CUBE_OFFSET));
        drawSquare(xSquare(CUBE_RADIUS));  switchTexture(3); draw9SquaresX(xSquare(CUBE_OFFSET));
        drawSquare(ySquare(-CUBE_RADIUS)); switchTexture(4); draw9SquaresY(ySquare(-CUBE_OFFSET));
        drawSquare(ySquare(CUBE_RADIUS));  switchTexture(5); draw9SquaresY(ySquare(CUBE_OFFSET));
        
        if (rotating) {
            xRot += xSpeed;
            yRot += ySpeed;
            zRot += zSpeed;
        }
        
        SDL_GL_SwapWindow (w);
        
    }
    
    release();
    return 0;
}

void initOGL() {
    SDL_Init (SDL_INIT_VIDEO);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION,2);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION,1);
    
    w = SDL_CreateWindow ("Shapes",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    SDL_GL_CreateContext (w); //associates the OpenGL commands to window w.
    SDL_GL_SetSwapInterval (1);
    
    glShadeModel (GL_SMOOTH);
    glClearColor (0,1,0,0);
    glClearDepth (1);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    glHint (GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    
    double ratio = ((double)SCREEN_WIDTH) / ((double)SCREEN_HEIGHT);
    glViewport (0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-tan(45.0/360*PI)*0.1*ratio,tan(45.0/360*PI)*0.1*ratio,-tan(45.0/360*PI)*0.1,tan(45.0/360*PI)*0.1,0.1,100);
}

void initTextures() {
    TI = new SDL_Surface *[6];
    TI[0] = IMG_Load ("media/dragonite.png");
    TI[1] = IMG_Load ("media/clefairy.png");
    TI[2] = IMG_Load ("media/bulbasaur.png");
    TI[3] = IMG_Load ("media/ekans.png");
    TI[4] = IMG_Load ("media/koffing.png");
    TI[5] = IMG_Load ("media/voltorb.png");
    texture = new GLuint[6];
    glGenTextures (6,texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity ();
}

// Frees memory.
void release() {
    for (int i = 0; i < 6; i++)
        SDL_FreeSurface (TI[i]);
    delete[] TI;
}

// Called before drawing each of the cube's sides.
void predraw() {
    glLoadIdentity();
    glTranslatef(0, 0, SCREEN_ZOOM);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
}

// Draws a black square defined by 'sq'.
void drawSquare(Square sq) {
    predraw();
    glColor3f(0, 0, 0);
    
    glBegin(GL_QUADS);
    
    drawPoint3f(sq.bottomLeft);
    drawPoint3f(sq.bottomRight);
    drawPoint3f(sq.topRight);
    drawPoint3f(sq.topLeft);
    
    glEnd ();
}

// Draws 9 small squares in a 3x3 grid format based off of 'smBaseSq'.
// 'pFunc' is used to get the 4 points of each individual square.
void draw9Squares(Square smBaseSq, PieceFunction pFunc) {
    predraw();
    glColor3f(1, 1, 1);
    
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++) {
            glBegin(GL_QUADS);
            
            glTexCoord2f(0.0 + (SM_SQ_SIZE * c), 0.0 + (SM_SQ_SIZE * r));
            drawPoint3f(pFunc(smBaseSq.bottomLeft, r, c));
            
            glTexCoord2f(0.0 + (SM_SQ_SIZE * c) + SM_SQ_SIZE, 0.0 + (SM_SQ_SIZE * r));
            drawPoint3f(pFunc(smBaseSq.bottomRight, r, c));
            
            glTexCoord2f(0.0 + (SM_SQ_SIZE * c) + SM_SQ_SIZE, 0.0 + (SM_SQ_SIZE * r) + SM_SQ_SIZE);
            drawPoint3f(pFunc(smBaseSq.topRight, r, c));
            
            glTexCoord2f(0.0 + (SM_SQ_SIZE * c), 0.0 + (SM_SQ_SIZE * r) + SM_SQ_SIZE);
            drawPoint3f(pFunc(smBaseSq.topLeft, r, c));
            
            glEnd ();
        }
}

// Draws 9 small squares inside 'bigSq'. The Z coordinate of 'bigSq' is constant.
void draw9SquaresZ(Square bigSq) {
    double smSqSize = SM_SQ_SIZE;
    double sF = SM_SQ_SHRINK;
    
    // the bottom left small square
    Point bottomLeft = newPoint(bigSq.bottomLeft.x + sF, bigSq.bottomLeft.y + sF, bigSq.bottomLeft.z);
    Point bottomRight = newPoint(bottomLeft.x - (2 * sF) + smSqSize, bottomLeft.y, bottomLeft.z);
    Point topRight = newPoint(bottomRight.x, bottomRight.y - (2 * sF) + smSqSize, bottomRight.z);
    Point topLeft = newPoint(bottomLeft.x, topRight.y, topRight.z);
    
    Square baseSq = newSquare(topRight, topLeft, bottomLeft, bottomRight);
    draw9Squares(baseSq, zPiecePoint);
}

// Draws 9 small squares inside 'bigSq'. The X coordinate of 'bigSq' is constant.
void draw9SquaresX(Square bigSq) {
    double smSqSize = SM_SQ_SIZE;
    double sF = SM_SQ_SHRINK;
    
    // the bottom left small square
    Point bottomLeft = newPoint(bigSq.bottomLeft.x, -bigSq.bottomLeft.y + sF, -bigSq.bottomLeft.z + sF);
    Point bottomRight = newPoint(bottomLeft.x, bottomLeft.y, bottomLeft.z - (2 * sF) + smSqSize);
    Point topRight = newPoint(bottomRight.x, bottomRight.y - (2 * sF) + smSqSize, bottomRight.z);
    Point topLeft = newPoint(bottomLeft.x, topRight.y, bottomLeft.z);
    
    Square baseSq = newSquare(topRight, topLeft, bottomLeft, bottomRight);
    draw9Squares(baseSq, xPiecePoint);
}

// Draws 9 small squares inside 'bigSq'. The Y coordinate of 'bigSq' is constant.
void draw9SquaresY(Square bigSq) {
    double smSqSize = SM_SQ_SIZE;
    double sF = SM_SQ_SHRINK;
    
    // the bottom left small square
    Point bottomLeft = newPoint(bigSq.bottomLeft.x + sF, bigSq.bottomLeft.y, -bigSq.bottomLeft.z + sF);
    Point bottomRight = newPoint(bottomLeft.x - (2 * sF) + smSqSize, bottomLeft.y, bottomLeft.z);
    Point topRight = newPoint(bottomRight.x, bottomRight.y, bottomRight.z - (2 * sF) + smSqSize);
    Point topLeft = newPoint(bottomLeft.x, topRight.y, topRight.z);
    
    Square baseSq = newSquare(topRight, topLeft, bottomLeft, bottomRight);
    draw9Squares(baseSq, yPiecePoint);
}

// Wrapper for glVertex3f to use the 'Point' struct.
void drawPoint3f(Point p) {
    glVertex3f(p.x, p.y, p.z);
}

// Returns a Point for a piece of a grid. 'base' is the first point (i.e. bottom right).
// The Z coordinate is constant.
Point zPiecePoint(Point base, int row, int col) {
    return newPoint(base.x + pieceOffset(col), base.y + pieceOffset(row), base.z);
}

// Returns a Point for a piece of a grid. 'base' is the first point (i.e. bottom right).
// The X coordinate is constant.
Point xPiecePoint(Point base, int row, int col) {
    return newPoint(base.x, base.y + pieceOffset(row), base.z + pieceOffset(col));
}

// Returns a Point for a piece of a grid. 'base' is the first point (i.e. bottom right).
// The Y coordinate is constant.
Point yPiecePoint(Point base, int row, int col) {
    return newPoint(base.x + pieceOffset(col), base.y, base.z + pieceOffset(row));
}

// Calculates the offset coordinate of a piece based on 'modifier'.
// Multiplies 'modifier' by the size of one 'piece' of the grid.
double pieceOffset(int modifier) {
    return (modifier * (CUBE_SIZE / 3));
}

// Returns a 1x1 unit square on the z-axis.
Square zSquare(double z) {
    Square sq;
    double r = CUBE_RADIUS;
    
    sq.bottomRight = newPoint(r, -r, z);
    sq.bottomLeft = newPoint(-r, -r, z);
    sq.topLeft = newPoint(-r, r, z);
    sq.topRight = newPoint(r, r, z);
    
    return sq;
}

// Returns a 1x1 unit square on the x-axis.
Square xSquare(double x) {
    Square sq;
    double r = CUBE_RADIUS;
    
    sq.bottomRight = newPoint(x, -r, r);
    sq.bottomLeft = newPoint(x, r, r);
    sq.topLeft = newPoint(x, r, -r);
    sq.topRight = newPoint(x, -r, -r);
    
    return sq;
}

// Returns a 1x1 unit square on the y-axis.
Square ySquare(double y) {
    Square sq;
    double r = CUBE_RADIUS;
    
    sq.bottomRight = newPoint(r, y, r);
    sq.bottomLeft = newPoint(-r, y, r);
    sq.topLeft = newPoint(-r, y, -r);
    sq.topRight = newPoint(r, y, -r);
    
    return sq;
}

// Switches the current texture.
void switchTexture(int index) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, TI[index]->w, TI[index]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, TI[index]->pixels);
}

// Handles key presses.
void onKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            xSpeed = ROTATION_SPEED;
            rotating = true;
            break;
            
        case SDLK_RIGHT:
            ySpeed = ROTATION_SPEED;
            rotating = true;
            break;
            
        case SDLK_DOWN:
            xSpeed = -ROTATION_SPEED;
            rotating = true;
            break;
            
        case SDLK_LEFT:
            ySpeed = -ROTATION_SPEED;
            rotating = true;
            break;
            
        case SDLK_a:
            zSpeed = ROTATION_SPEED;
            rotating = true;
            break;
            
        case SDLK_z:
            zSpeed = -ROTATION_SPEED;
            rotating = true;
            break;
            
        case SDLK_SPACE:
            rotating = false;
            break;
            
        case SDLK_r:
            resetRotationVariables();
            rotating = false;
            break;
            
        default:
            break;
    }
}

void resetRotationVariables() {
    xRot = yRot = zRot = xSpeed = ySpeed = zSpeed = 0;
}

Point newPoint(double x, double y, double z) {
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

Square newSquare(Point topRight, Point topLeft, Point bottomLeft, Point bottomRight) {
    Square s;
    s.topRight = topRight;
    s.bottomRight = bottomRight;
    s.topLeft = topLeft;
    s.bottomLeft = bottomLeft;
    return s;
}
