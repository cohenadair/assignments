//
//  Hud.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-15.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Hud_h
#define Hud_h

#include "Rect.h"

class Hud {
    
private:
    bool isHelping;
    Uint32 prevTicks;
    
    Rect *rectFullScreen;
    Rect *rectHelp;
    Rect *rectKey;
    
    int charHeight;
    int charWidth;
    
    // display
    void drawScore();
    void drawHelp();
    void drawInstructions();
    void drawGameOverFailed();
    void drawPlay();
    void drawKey();
    void drawLevelComplete();
    void drawNoKey();
    void drawNumber(long number, Point *start);

public:
    Hud();
    ~Hud();
    
    // accessing
    bool getIsHelping();
    void setIsHelping(bool helping);
    
    // drawing
    void draw();
    
    // updating
    void updateScore();
    
};

#endif
