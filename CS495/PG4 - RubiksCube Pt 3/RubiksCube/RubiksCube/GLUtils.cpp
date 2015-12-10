//
//  GLUtils.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "GLUtils.h"

SDL_Window *GLUtils::window;
GLuint *GLUtils::textures;

// initializing
void GLUtils::init() {
    SDL_Init (SDL_INIT_VIDEO);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION,2);
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION,1);
    
    window = SDL_CreateWindow ("Shapes",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,kScreenWidth,kScreenHeight,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
    SDL_GL_CreateContext (window); //associates the OpenGL commands to window w.
    SDL_GL_SetSwapInterval (1);
    
    glShadeModel (GL_SMOOTH);
    glClearColor (0,1,0,0);
    glClearDepth (1);
    glEnable (GL_TEXTURE_2D);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    glHint (GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    
    double ratio = ((double)kScreenWidth) / ((double)kScreenHeight);
    glViewport (0,0,kScreenWidth,kScreenHeight);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    glFrustum (-tan(45.0/360*kPi)*0.1*ratio,tan(45.0/360*kPi)*0.1*ratio,-tan(45.0/360*kPi)*0.1,tan(45.0/360*kPi)*0.1,0.1,100);
    glMatrixMode(GL_MODELVIEW);
}

// getters and setters
SDL_Window * GLUtils::getWindow() {
    return window;
}

// drawing
void GLUtils::loadTextures() {
    textures = new GLuint[kNumberOfCubeSides];
    glGenTextures(kNumberOfCubeSides, textures);
    
    loadTexture(textures[kFaceFront], "media/dragonite.png");
    loadTexture(textures[kFaceBack], "media/clefairy.png");
    loadTexture(textures[kFaceTop], "media/bulbasaur.png");
    loadTexture(textures[kFaceBottom], "media/ekans.png");
    loadTexture(textures[kFaceLeft], "media/koffing.png");
    loadTexture(textures[kFaceRight], "media/voltorb.png");
}

void GLUtils::loadTexture(GLuint texture, const char *fileName) {
    SDL_Surface *img = IMG_Load(fileName);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, img->pixels);
    
    SDL_FreeSurface(img);
}

void GLUtils::switchTexture(int index) {
    glBindTexture(GL_TEXTURE_2D, textures[index]);
}

// rotating
void GLUtils::rotateOnAxis(int angle, int axis) {
    if (axis == kAxisX)
        glRotatef(angle, 1, 0, 0);
    else if (axis == kAxisY)
        glRotatef(angle, 0, 1, 0);
    else if (axis == kAxisZ)
        glRotatef(angle, 0, 0, 1);
    else
        cout << "Invalid rotation axis: " << axis << endl;
}

// memory management
void GLUtils::release() {
    delete textures;
}
