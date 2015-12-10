//
//  Hud.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-15.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Hud.h"

Hud::Hud() {
    isHelping = false;
    prevTicks = 0;
    
    rectFullScreen = new Rect(
        new Point(kScreenWidth, 0),
        new Point(0, 0),
        new Point(0, kScreenHeight),
        new Point(kScreenWidth, kScreenHeight)
    );
    
    SDL_Surface *help = IMG_Load("images/help.png");
    rectHelp = new Rect(
        new Point(kScreenWidth - 5, kScreenHeight - 5 - help->h),
        new Point(kScreenWidth - 5 - help->w, kScreenHeight - 5 - help->h),
        new Point(kScreenWidth - 5 - help->w, kScreenHeight - 5),
        new Point(kScreenWidth - 5, kScreenHeight - 5)
    );
    SDL_FreeSurface(help);
    
    rectKey = new Rect(
        new Point(100 + 5, kScreenHeight - 5 - 42),
        new Point(5, kScreenHeight - 5 - 42),
        new Point(5, kScreenHeight - 5),
        new Point(100 + 5, kScreenHeight - 5)
    );
    
    // get the width and height for individial digit characters
    // used to calculate Rect coordinates
    SDL_Surface *img = IMG_Load("images/0.png");
    charWidth = img->w;
    charHeight = img->h;
    SDL_FreeSurface(img);
}

Hud::~Hud() {
    delete rectFullScreen;
    delete rectHelp;
    delete rectKey;
}

void Hud::draw() {
    GLUtils::begin2DDrawing();
    
    drawHelp();
    drawScore();
    drawInstructions();
    drawGameOverFailed();
    drawKey();
    drawPlay();
    drawLevelComplete();
    drawNoKey();
    
    GLUtils::end2DDrawing();
}

void Hud::drawScore() {
    string score = to_string((long long)Game::getScore());
    drawNumber(Game::getScore(), new Point(kScreenWidth / 2 - (score.length() / 2 * charWidth), 5));
}

void Hud::drawHelp() {
    rectHelp->draw2D(kTextureHelp);
}

void Hud::drawInstructions() {
    if (isHelping)
        rectFullScreen->draw2D(kTextureInstructions);
}

void Hud::drawGameOverFailed() {
    if (Game::isOverFailed() && !isHelping)
        rectFullScreen->draw2D(kTextureGameOver);
}

void Hud::drawPlay() {
    if (Game::isPaused() && !isHelping)
        rectFullScreen->draw2D(kTexturePlay);
}

void Hud::drawKey() {
    if (Game::isKeyFound() && !isHelping)
        rectKey->draw2D(kTextureKey);
}

void Hud::drawLevelComplete() {
    if (Game::isOverSuccess() && !isHelping)
        rectFullScreen->draw2D(kTextureLevelComplete);
}

void Hud::drawNoKey() {
    if (Game::isNearDoor() && !Game::isKeyFound() && !isHelping)
        rectFullScreen->draw2D(kTextureNoKey);
}

void Hud::drawNumber(long number, Point *start) {
    string str = to_string((long long)number);
    
    for (int i = 0; i < str.length(); i++) {
        Rect *r = new Rect(
           new Point(start->getX() + charWidth + (i * charWidth), start->getY()),
           new Point(start->getX() + i * charWidth, start->getY()),
           new Point(start->getX() + i * charWidth, start->getY() + charHeight),
           new Point(start->getX() + charWidth + (i * charWidth), start->getY() + charHeight)
        );
        
        r->draw2D(str[i] - '0');
        delete r;
    }
    
    delete start;
}

// accessing
bool Hud::getIsHelping() {
    return isHelping;
}

void Hud::setIsHelping(bool helping) {
    isHelping = helping;
}

// updating
void Hud::updateScore() {
    if (Game::isOver())
        return;
    
    if (((SDL_GetTicks() - prevTicks) / 1000) >= 1) {
        Game::updateScore();
        prevTicks = SDL_GetTicks();
    }
}


