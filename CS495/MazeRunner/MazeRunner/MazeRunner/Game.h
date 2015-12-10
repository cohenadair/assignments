//
//  Game.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-24.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Game_h
#define Game_h

class Game {
    
private:
    static int score;
    static float speed;
    static bool paused;
    static bool keyFound;
    static bool nearDoor;
    static bool hitBlackHole;
    static bool hitFire;
    
public:
    // initializing
    static void init();
    
    // accessing
    static int getScore();
    static float getSpeed();
    static bool isPaused();
    static bool isKeyFound();
    static bool isNearDoor();
    static bool didHitBlackHole();
    static bool didHitFire();
    
    // status
    static bool isOver();
    static bool isOverFailed();
    static bool isOverSuccess();
    static void updateScore();
    static void togglePaused();
    static void pause();
    static void play();
    static void setSpeed(float f);
    static void setKeyFound(bool found);
    static void setNearDoor(bool near);
    static void setHitBlackHole(bool b);
    static void setHitFire(bool b);
    static void incScoreBy(int incBy);
    
};

#endif
