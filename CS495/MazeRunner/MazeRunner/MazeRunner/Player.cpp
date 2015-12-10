//
//  Player.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-13.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Player.h"

Player::Player(Maze *maze) {
    pos = maze->getStartPosition();
    start = pos->clone();
    angle = 0;
    turning = false;
    turningCounter = 0;
    this->maze = maze;
}

Player::~Player() {
    delete pos;
    delete start;
}

// accessing
Point * Player::getPos() {
    return pos;
}

void Player::setPos(Point *p) {
    pos = p;
}

void Player::incXPos(float incBy) {
    pos->setX(pos->getX() + incBy);
}

void Player::incZPos(float incBy) {
    pos->setZ(pos->getZ() + incBy);
}

bool Player::getTurning() {
    return turning;
}

void Player::setTurning(bool b) {
    turning = b;
}

// gameplay
void Player::reset() {
    goToOrigin();
    glRotatef(angle, 0, 1, 0);
    angle = 0;
}

void Player::goToPosition() {
    pos->traslate();
}

void Player::goToOrigin() {
    Point *posCopy = pos->clone();
    posCopy->invert();
    posCopy->traslate();
    delete posCopy;
}

void Player::beginTurn(bool clockwise) {
    turning = true;
    turningClockwise = clockwise;
    turn();
}

void Player::turnLeft() {
    if (turning)
        return;
    
    angle = (abs(90 + angle + 360) % 360);
    beginTurn(false);
}

void Player::turnRight() {
    if (turning)
        return;
    
    angle -= 90;
    if (angle < 0)
        angle = 270;
    
    beginTurn(true);
}

void Player::turn() {
    if (!turning)
        return;
    
    float turningStep = 5.0;
    
    turningCounter += turningStep;
    if (turningCounter == 90) {
        turning = false;
        turningCounter = 0;
    }
    
    goToOrigin();
    glRotatef(turningStep * (turningClockwise ? 1 : -1), 0, 1, 0);
    goToPosition();
}

void Player::moveForward() {
    move(maze, getStepX(90), getStepZ(0));
}

void Player::moveBackward() {
    move(maze, getStepX(270), getStepZ(180));
}

void Player::moveLeft() {
    move(maze, getStepZ(0), getStepX(270));
}

void Player::moveRight() {
    move(maze, getStepZ(180), getStepX(90));
}

void Player::move(Maze *maze, float stepX, float stepZ) {
    if (turning)
        return;
    
    updatePosition(stepX, stepZ);
    
    // reverse the X and Z coordinates
    // not sure why this is needed; will come back to it later
    Point *p = pos->clone();
    p->setZ(p->getZ() * -1);
    p->setX(p->getX() * -1);
    
    if (maze->isPointNearWall(p))
        updatePosition(-stepX, -stepZ); // reverse position if near a wall
    else
        glTranslatef(stepX, 0, stepZ);
    
    lookForKey(p);
    tryToExit(p);
    handleObstacle(p);
    handleBlackHole();
    handleFire();
    
    delete p;
}

float Player::getStepX(int positiveStepAngle) {
    return (abs(angle) == 90 || abs(angle) == 270) * (abs(angle) == positiveStepAngle ? Game::getSpeed() : -Game::getSpeed());
}

float Player::getStepZ(int positiveStepAngle) {
    return (abs(angle) == 0 || abs(angle) == 180) * (abs(angle) == positiveStepAngle ? Game::getSpeed() : -Game::getSpeed());
}

void Player::updatePosition(float stepX, float stepZ) {
    pos->setZ(pos->getZ() + stepZ);
    pos->setX(pos->getX() + stepX);
}

void Player::lookForKey(Point *position) {
    // if it's already found, there's no need to look for it again
    if (Game::isKeyFound())
        return;
    
    if (maze->isPointNearKey(position)) {
        Game::setKeyFound(true);
        Game::incScoreBy(2500);
    }
}

void Player::tryToExit(Point *position) {
    Game::setNearDoor(maze->isPointNearExit(position));
}

void Player::handleObstacle(Point *position) {
    Obstacle *obstacle = maze->isPointNearObstacle(position);
    if (obstacle != NULL)
        obstacle->executePlayerFound();
}

void Player::handleBlackHole() {
    if (Game::didHitBlackHole()) {
        reset();
        pos = start->clone();
        goToPosition();
        
        Game::setHitBlackHole(false);
    }
}

void Player::handleFire() {
    if (Game::didHitFire()) {
        // move backwards 10 times
        for (int i = 0; i < 10; i++) {
            updatePosition(getStepX(270), getStepZ(180));
            glTranslatef(getStepX(270), 0, getStepZ(180));
        }
        
        Game::setHitFire(false);
    }
}






