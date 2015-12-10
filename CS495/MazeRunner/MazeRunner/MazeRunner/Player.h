//
//  Player.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-13.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include "Maze.h"

class Player {
    
private:
    Maze *maze;
    Point *pos;
    Point *start;
    int angle;
    
    // turning animation
    bool turning;
    bool turningClockwise;
    float turningCounter;
    
    // gameplay
    float getStepX(int positiveStepAngle);
    float getStepZ(int positiveStepAngle);
    void updatePosition(float stepX, float stepZ);
    void move(Maze *maze, float stepX, float stepZ);
    void beginTurn(bool clockwise);
    void lookForKey(Point *position);
    void tryToExit(Point *position);
    void handleObstacle(Point *position);
    void handleBlackHole();
    void handleFire();
    
public:
    Player(Maze *maze);
    ~Player();
    
    // accessing
    Point * getPos();
    void setPos(Point *p);
    void incXPos(float incBy);
    void incZPos(float incBy);
    void setTurning(bool b);
    bool getTurning();
    
    // gameplay
    void reset();
    void goToPosition();
    void goToOrigin();
    void turnLeft();
    void turnRight();
    void turn();
    void moveForward();
    void moveBackward();
    void moveLeft();
    void moveRight();
    
};

#endif
