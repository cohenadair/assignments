//
//  main.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-09-23.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "main.h"

int main(int argc, char **argv) {
    GLUtils::init();
    GLUtils::loadTextures();
    
    rotating = shiftIsDown = false;
    xSpeed = ySpeed = zSpeed = 0;
    
    SDL_Event event;
    
    rubixCube = new Cube();

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            
            if (event.type == SDL_KEYDOWN)
                onKeyPress(event.key.keysym.sym);
            
            if (event.type == SDL_KEYUP)
                onKeyUp(event.key.keysym.sym);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(0, 0, 0);
        
        rubixCube->draw();
        
        if (rotating) {
            rubixCube->incXRot(xSpeed);
            rubixCube->incYRot(ySpeed);
            rubixCube->incZRot(zSpeed);
        }
        
        SDL_GL_SwapWindow(GLUtils::getWindow());
    }
    
    delete rubixCube;
    GLUtils::release();
    
    return 0;
}

// Handles key up.
void onKeyUp(SDL_Keycode key) {
    switch (key) {
        case SDLK_RSHIFT: case SDLK_LSHIFT:
            shiftIsDown = false;
            break;
    }
}

// Handles key presses.
void onKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            xSpeed = kRotationSpeed;
            rotating = true;
            break;
            
        case SDLK_RIGHT:
            ySpeed = kRotationSpeed;
            rotating = true;
            break;
            
        case SDLK_DOWN:
            xSpeed = -kRotationSpeed;
            rotating = true;
            break;
            
        case SDLK_LEFT:
            ySpeed = -kRotationSpeed;
            rotating = true;
            break;
            
        case SDLK_a:
            zSpeed = kRotationSpeed;
            rotating = true;
            break;
            
        case SDLK_z:
            zSpeed = -kRotationSpeed;
            rotating = true;
            break;
            
        case SDLK_SPACE:
            rotating = false;
            break;
            
        case SDLK_1:
            rotateSide(kFaceFront, !shiftIsDown);
            break;
            
        case SDLK_2:
            rotateSide(kFaceBack, !shiftIsDown);
            break;
            
        case SDLK_3:
            rotateSide(kFaceTop, !shiftIsDown);
            break;
            
        case SDLK_4:
            rotateSide(kFaceBottom, !shiftIsDown);
            break;
            
        case SDLK_5:
            rotateSide(kFaceLeft, !shiftIsDown);
            break;
            
        case SDLK_6:
            rotateSide(kFaceRight, !shiftIsDown);
            break;
            
        case SDLK_RSHIFT: case SDLK_LSHIFT:
            shiftIsDown = true;
            break;
    }
}

void rotateSide(int faceId, bool clockwise) {
    if (clockwise)
        rubixCube->rotateClockwise(faceId);
    else
        rubixCube->rotateCounterclockwise(faceId);
}
