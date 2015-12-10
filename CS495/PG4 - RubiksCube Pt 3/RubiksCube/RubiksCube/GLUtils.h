//
//  GLUtils.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef GLUtils_h
#define GLUtils_h

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include "glQuaternion.h"
#include "constants.h"
using namespace std;

class GLUtils {
    
private:
    static SDL_Window *window;
    static GLuint *textures;

public:
    // initializing
    static void init();
    
    // getters and setters
    static SDL_Window * getWindow();
    
    // drawing
    static void loadTextures();
    static void loadTexture(GLuint texture, const char *fileName);
    static void switchTexture(int index);
    
    // rotating
    static void rotateOnAxis(int angle, int axis);
    
    // memory management
    static void release();

};

#endif
