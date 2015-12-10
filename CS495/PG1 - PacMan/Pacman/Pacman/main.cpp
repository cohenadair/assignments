//
//  main.cpp
//  Pacman
//
//  Created by Cohen Adair on 2015-08-31.
//  Copyright (c) 2015 Cohen Adair. All rights reserved.
//

#include "main.h"

int main(int argc, char ** argv) {
    init();
    draw();
    
    SDL_Event event;
    
    while (true) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            
            if (event.type == SDL_KEYDOWN)
                onKeyPress(event.key.keysym.sym);
        }
        
        move();
        attemptToEat();
        redraw();
    }
    
    close();
    return 0;
}

void init() {
    // SDL stuff
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    
    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, kScreenW, kScreenH, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);
    
    // pacman stuff
    pacmanX = pacmanY = 0;
    pacmanW = pacmanH = 50;
    foodW = foodH = 10;
    relocateFood();

    currentDirection = kRight;
    currentVariation = kOpened;
    
    // open, close toggle timer
    SDL_AddTimer(250, toggleMouthCallback, NULL);
}

void close() {
    // free image surfaces
    for (int i = 0; i < kNumberOfDirections; i++)
        for (int j = 0; j < kNumberOfVariations; j++)
            SDL_FreeSurface(pacmanImages[i][j]);
    
    SDL_FreeSurface(foodImage);
    Mix_FreeChunk(chompSound);
    Mix_FreeChunk(sirenSound);
    
    SDL_FreeSurface(surface);
    SDL_DestroyWindow(window);
    Mix_Quit();
    SDL_Quit();
}

// initialization of images and sounds
void draw() {
    // pacman
    pacmanImages.resize(kNumberOfDirections);
    for (int i = 0; i < kNumberOfDirections; i++)
        pacmanImages[i].resize(kNumberOfVariations);
    
    pacmanImages[kUp][0]    = IMG_Load("media/closed_up.png");
    pacmanImages[kUp][1]    = IMG_Load("media/opened_up.png");
    pacmanImages[kRight][0] = IMG_Load("media/closed_right.png");
    pacmanImages[kRight][1] = IMG_Load("media/opened_right.png");
    pacmanImages[kDown][0]  = IMG_Load("media/closed_down.png");
    pacmanImages[kDown][1]  = IMG_Load("media/opened_down.png");
    pacmanImages[kLeft][0]  = IMG_Load("media/closed_left.png");
    pacmanImages[kLeft][1]  = IMG_Load("media/opened_left.png");
    
    // food
    foodImage = IMG_Load("media/food.png");
    
    // sounds
    chompSound = Mix_LoadWAV("media/chomp.wav");
    sirenSound = Mix_LoadWAV("media/siren.wav");
    Mix_PlayChannelTimed(-1, sirenSound, -1, -1);
}

void redraw() {
    // black background
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0, 0, 0));
    
    // draw pacman
    SDL_Rect *pacmanDest = newRect(pacmanX, pacmanY, pacmanW, pacmanH);
    SDL_BlitScaled(pacmanImages[currentDirection][currentVariation], NULL, surface, pacmanDest);
    delete pacmanDest;
    
    // draw food
    SDL_Rect *foodDest = newRect(foodX, foodY, foodW, foodH);
    SDL_BlitScaled(foodImage, NULL, surface, foodDest);
    delete foodDest;
    
    SDL_UpdateWindowSurface(window);
}

// moves Pacman in the correct direction
void move() {
    if (isOnEdge())
        return;
    
    double incBy = 0.5;
    
    switch (currentDirection) {
        case kUp:
            pacmanY -= incBy;
            break;
            
        case kRight:
            pacmanX += incBy;
            break;
            
        case kDown:
            pacmanY += incBy;
            break;
            
        case kLeft:
            pacmanX -= incBy;
            break;
            
        default:
            break;
    }
}

// used in an SDL_Timer to toggle Pacman's mouth
Uint32 toggleMouthCallback(Uint32 interval, void *param) {
    // cycle between mouth variations
    currentVariation = ++currentVariation % kNumberOfVariations;
    return interval;
}

void onKeyPress(SDL_Keycode key) {
    switch (key) {
        case SDLK_UP:
            currentDirection = kUp;
            break;
            
        case SDLK_RIGHT:
            currentDirection = kRight;
            break;
            
        case SDLK_DOWN:
            currentDirection = kDown;
            break;
            
        case SDLK_LEFT:
            currentDirection = kLeft;
            break;
            
        default:
            break;
    }
}

// returns true if Pacman is on the edge of the screen
bool isOnEdge() {
    // left
    if (pacmanX < kScreenX) {
        pacmanX = kScreenX;
        return true;
    }
    
    // top
    if (pacmanY < kScreenY) {
        pacmanY = kScreenY;
        return true;
    }
    
    // right
    if (pacmanX + pacmanW > kScreenW) {
        pacmanX = kScreenW - pacmanW;
        return true;
    }
    
    // bottom
    if (pacmanY + pacmanH > kScreenH) {
        pacmanY = kScreenH - pacmanH;
        return true;
    }
    
    return false;
}

// compares Pacman's location to the food's location
// if Pacman and the food collides a sound is played and the food is relocated
void attemptToEat() {
    double pacmanRadius = pacmanW / 2;
    double pacmanCenterX = pacmanX + pacmanW - pacmanRadius;
    double pacmanCenterY = pacmanY + pacmanH - pacmanRadius;
    
    double foodRadius = foodW / 2;
    double foodCenterX = foodX + foodW - foodRadius;
    double foodCenterY = foodY + foodH - foodRadius;
    
    double dist = (pacmanRadius / 2 + foodRadius);
    
    // distance between centers < sum of radii
    if (distanceBetweenPoints(pacmanCenterX, pacmanCenterY, foodCenterX, foodCenterY) < dist) {
        Mix_PlayChannel(-1, chompSound, 0);
        relocateFood();
    }
}

void relocateFood() {
    int padding = 10;
    
    foodX = rand() % (kScreenW - padding) + 1;
    foodY = rand() % (kScreenH - padding) + 1;
}

SDL_Rect * newRect(int x, int y, int w, int h) {
    SDL_Rect *result = new SDL_Rect;
    
    result->x = x;
    result->y = y;
    result->w = w;
    result->h = h;
    
    return result;
}

double distanceBetweenPoints(int x1, int y1, int x2, int y2) {
    int sqDeltaX = (x2 - x1);
    sqDeltaX *= sqDeltaX;
    
    int sqDeltaY = (y2 - y1);
    sqDeltaY *= sqDeltaY;
    
    return sqrt((double)(sqDeltaX + sqDeltaY));
}
