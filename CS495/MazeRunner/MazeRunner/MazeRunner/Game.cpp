//
//  Game.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-24.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Game.h"

int Game::score;
float Game::speed;
bool Game::paused;
bool Game::keyFound;
bool Game::nearDoor;
bool Game::hitBlackHole;
bool Game::hitFire;

// initializing
void Game::init() {
    score = 10000;
    speed = 0.15;
    paused = true;
    keyFound = false;
    nearDoor = false;
    hitBlackHole = false;
    hitFire = false;
}

// accessing
int Game::getScore() {
    return score;
}

float Game::getSpeed() {
    return speed;
}

bool Game::isPaused() {
    return paused;
}

bool Game::isKeyFound() {
    return keyFound;
}

bool Game::isNearDoor() {
    return nearDoor;
}

bool Game::didHitBlackHole() {
    return hitBlackHole;
}

bool Game::didHitFire() {
    return hitFire;
}

// status
bool Game::isOver() {
    return isOverFailed() || isOverSuccess();
}

bool Game::isOverSuccess() {
    return nearDoor && keyFound;
}

bool Game::isOverFailed() {
    return score <= 0;
}

void Game::updateScore() {
    if (paused)
        return;
    
    score -= 15;
    if (score <= 0)
        score = 0;
}

void Game::togglePaused() {
    paused = !paused;
}

void Game::pause() {
    paused = true;
}

void Game::play() {
    paused = false;
}

void Game::setSpeed(float f) {
    speed = f;
}

void Game::setKeyFound(bool found) {
    keyFound = found;
}

void Game::setNearDoor(bool near) {
    nearDoor = near;
}

void Game::setHitBlackHole(bool b) {
    hitBlackHole = b;
}

void Game::setHitFire(bool b) {
    hitFire = b;
}

void Game::incScoreBy(int incBy) {
    score += incBy;
    if (score <= 0)
        score = 0;
}
