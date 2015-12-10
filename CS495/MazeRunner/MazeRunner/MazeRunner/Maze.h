//
//  Maze.h
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Maze_h
#define Maze_h

#include "SpeedBoost.h"
#include "ScoreBoost.h"
#include "BlackHole.h"
#include "Fire.h"

class Maze {
    
private:
    int numOfWalls;
    Point *start;
    Rect *key;
    Rect *exit;
    Rect **walls;
    Rect *floor;
    Rect *ceiling;
    
    int numOfObstacles;
    Obstacle **obstacles;
    
    void loadFromFile(char *filePath);
    void readStr(FILE *file, char *inString);
    float readFloat(FILE *file);
    Point * readPoint(FILE *file);
    Rect * readRect(FILE *file);
    void readObstacles(FILE *file);
    void readWalls(FILE *file);
    
public:
    Maze(char *fileName);
    ~Maze();
    
    // accessing
    Point * getStartPosition();
    
    // drawing
    void draw();
    
    // gameplay
    bool isPointNearWall(Point *p);
    bool isPointNearKey(Point *p);
    bool isPointNearExit(Point *p);
    Obstacle * isPointNearObstacle(Point *p);
    
};

#endif
