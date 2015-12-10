//
//  main.cpp
//  rubiksCube
//
//  Created by Cohen Adair on 2015-09-23.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "main.h"

int main(int argc, char **argv) {
    GLUtils::init();
    GLUtils::loadTextures();
    
    shiftIsDown = false;
    xSpeed = ySpeed = zSpeed = 0;
    
    SDL_Event event;
    
    rubiksCube = new Cube();

    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            
            if (event.type == SDL_KEYDOWN)
                onKeyDown(event.key.keysym.sym);
            
            if (event.type == SDL_KEYUP)
                onKeyUp(event.key.keysym.sym);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        rubiksCube->draw();
        SDL_GL_SwapWindow(GLUtils::getWindow());
    }
    
    delete rubiksCube;
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
void onKeyDown(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            rubiksCube->setXRot(-kRotationSpeed);
            break;
            
        case SDLK_RIGHT:
            rubiksCube->setYRot(kRotationSpeed);
            break;
            
        case SDLK_DOWN:
            rubiksCube->setXRot(kRotationSpeed);
            break;
            
        case SDLK_LEFT:
            rubiksCube->setYRot(-kRotationSpeed);
            break;
            
        case SDLK_a:
            rubiksCube->setZRot(kRotationSpeed);
            break;
            
        case SDLK_z:
            rubiksCube->setZRot(-kRotationSpeed);
            break;
            
        case SDLK_SPACE:
            rubiksCube->stopRotation();
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
        rubiksCube->rotateClockwise(faceId);
    else
        rubiksCube->rotateCounterclockwise(faceId);
}
