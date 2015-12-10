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
    
    window = SDL_CreateWindow ("Maze Runner",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,kScreenWidth,kScreenHeight,SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
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
    textures = new GLuint[kNumberOfTextures];
    glGenTextures(kNumberOfTextures, textures);
    
    loadTexture(textures[kTexture0], "images/0.png");
    loadTexture(textures[kTexture1], "images/1.png");
    loadTexture(textures[kTexture2], "images/2.png");
    loadTexture(textures[kTexture3], "images/3.png");
    loadTexture(textures[kTexture4], "images/4.png");
    loadTexture(textures[kTexture5], "images/5.png");
    loadTexture(textures[kTexture6], "images/6.png");
    loadTexture(textures[kTexture7], "images/7.png");
    loadTexture(textures[kTexture8], "images/8.png");
    loadTexture(textures[kTexture9], "images/9.png");
    loadTexture(textures[kTextureBricks], "images/bricks.jpeg");
    loadTexture(textures[kTextureGround], "images/ground.jpeg");
    loadTexture(textures[kTextureCeiling], "images/ceiling.jpeg");
    loadTexture(textures[kTextureDoor], "images/door.jpeg");
    loadTexture(textures[kTextureInstructions], "images/instructions.png");
    loadTexture(textures[kTextureHelp], "images/help.png");
    loadTexture(textures[kTextureGameOver], "images/game_over.png");
    loadTexture(textures[kTexturePlay], "images/play.png");
    loadTexture(textures[kTextureKey], "images/key.png");
    loadTexture(textures[kTextureLevelComplete], "images/level_complete.png");
    loadTexture(textures[kTextureNoKey], "images/no_key.png");
    loadTexture(textures[kTextureFire], "images/fire.png");
    loadTexture(textures[kTextureBlackHole], "images/black_hole.png");
    loadTexture(textures[kTextureSpeedBoost], "images/speed_boost.png");
    loadTexture(textures[kTextureScoreBoost], "images/score_boost.png");
}

void GLUtils::loadTexture(GLuint texture, const char *fileName) {
    SDL_Surface *img = IMG_Load(fileName);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, img->pixels);
    
    SDL_FreeSurface(img);
}

void GLUtils::switchTexture(int index) {
    glBindTexture(GL_TEXTURE_2D, textures[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void GLUtils::begin2DDrawing() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, kScreenWidth, kScreenHeight, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void GLUtils::end2DDrawing() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// memory management
void GLUtils::release() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete textures;
}
