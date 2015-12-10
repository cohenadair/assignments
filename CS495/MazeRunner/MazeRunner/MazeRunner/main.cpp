//
//  main.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "main.h"

int main(int argc, char **argv) {
    GLUtils::init();
    GLUtils::loadTextures();
    
    SDL_Event event;
    
    restart();
    
    while (true) {
        if (quit)
            break;
        
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            
            if (event.type == SDL_KEYDOWN)
                onKeyDown(event.key.keysym.sym);
        }
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glTranslatef(0, 0, 0);
        
        // do drawing here
        currentMaze->draw();
        
        if (player->getTurning())
            player->turn();
        
        hud->updateScore();
        hud->draw();
        
        SDL_GL_SwapWindow(GLUtils::getWindow());
    }
    
    delete hud;
    delete player;
    delete currentMaze;
    
    GLUtils::release();
    
    return 0;
}

void restart() {
    Game::init();
    hud = new Hud();
    currentMaze = new Maze((char *)"levels/1");
    player = new Player(currentMaze);
    player->goToPosition();
    quit = false;
}

void goToNextLevel() {
    player->reset();
    restart();
}

// Handles key presses.
void onKeyDown(SDL_Keycode key) {
    switch (key) {
        case SDLK_ESCAPE:
            quit = true;
            break;
            
        case SDLK_h:
            Game::pause();
            hud->setIsHelping(true);
            break;
            
        case SDLK_c:
            hud->setIsHelping(false);
            break;
            
        case SDLK_r:
            player->reset();
            restart();
            break;
            
        case SDLK_p:
            if (!hud->getIsHelping())
                Game::togglePaused();
            break;
            
        case SDLK_n:
            if (Game::isOverSuccess())
                goToNextLevel();
            break;
            
        default:
            break;
    }
    
    if (Game::isOver() || Game::isPaused())
        return;
    
    switch (key) {
        case SDLK_o:
            player->goToOrigin();
            break;

        case SDLK_b:
            player->goToPosition();
            break;
            
        case SDLK_w:
            player->moveForward();
            break;
            
        case SDLK_s:
            player->moveBackward();
            break;
            
        case SDLK_a:
            player->moveLeft();
            break;
            
        case SDLK_d:
            player->moveRight();
            break;
            
        case SDLK_LEFT:
            player->turnLeft();
            break;
            
        case SDLK_RIGHT:
            player->turnRight();
            break;
    }
}




