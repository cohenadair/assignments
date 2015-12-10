//
//  Maze.cpp
//  MazeRunner
//
//  Created by Cohen Adair on 2015-11-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Maze.h"

Maze::Maze(char *filePath) {
    loadFromFile(filePath);
}

Maze::~Maze() {
    for (int i = 0; i < numOfWalls; i++)
        delete walls[i];
    
    for (int i = 0; i < numOfObstacles; i++)
        delete obstacles[i];
    
    delete walls;
    delete floor;
    delete ceiling;
    delete exit;
    delete key;
}

void Maze::loadFromFile(char *filePath) {
    FILE *in;
    in = fopen(filePath, "rt");

    numOfWalls = 0;
    numOfObstacles = 0;
    
    floor = readRect(in);
    ceiling = readRect(in);
    
    exit = readRect(in);
    start = readPoint(in);
    start->setX(start->getX() * -1);
    start->setZ(start->getZ() * -1);
    key = readRect(in);
    
    readObstacles(in);
    readWalls(in);
    
    fclose(in);
}

// reads in the next line from "file", skipping blank lines and comments
void Maze::readStr(FILE *file, char *inString) {
    do {
        fgets(inString, 255, file);
    } while (inString[0] == '/' || inString[0] == '\n');
}

float Maze::readFloat(FILE *file) {
    char line[255];
    float f = 0;
    readStr(file, line);
    sscanf(line, "%f", &f);
    return f;
}

Point * Maze::readPoint(FILE *file) {
    char line[255];
    float x, y, z;
    
    readStr(file, line);
    sscanf(line, "%f %f %f", &x, &y, &z);
    return new Point(x, y, z);
}

Rect * Maze::readRect(FILE *file) {
    Rect *rect = new Rect();
    
    rect->setLength(readFloat(file));
    rect->setTopRight(readPoint(file));
    rect->setTopLeft(readPoint(file));
    rect->setBottomLeft(readPoint(file));
    rect->setBottomRight(readPoint(file));
    
    return rect;
}

void Maze::readObstacles(FILE *file) {
    char line[255];
    
    readStr(file, line);
    sscanf(line, "numberOfObstacles %d\n", &numOfObstacles);
    
    obstacles = new Obstacle *[numOfObstacles];
    for (int i = 0; i < numOfObstacles; i++) {
        int type = (int)readFloat(file);
        
        switch (type) {
            case kSpeedBoost:
                obstacles[i] = new SpeedBoost(readRect(file));
                break;
                
            case kScoreBoost:
                obstacles[i] = new ScoreBoost(readRect(file));
                break;
                
            case kBlackHole:
                obstacles[i] = new BlackHole(readRect(file));
                break;
                
            case kFire:
                obstacles[i] = new Fire(readRect(file));
                break;
                
            default:
                break;
        }
    }
}

void Maze::readWalls(FILE *file) {
    char line[255];
    
    readStr(file, line);
    sscanf(line, "numberOfWalls %d\n", &numOfWalls);
    
    walls = new Rect *[numOfWalls];
    for (int i = 0; i < numOfWalls; i++)
        walls[i] = readRect(file);
}

// accessing
Point * Maze::getStartPosition() {
    return start;
}

// drawing
void Maze::draw() {
    glColor3f(1, 1, 1);
    for (int i = 0; i < numOfWalls; i++)
        walls[i]->draw(kTextureBricks, walls[i]->getLength() / 1.5, 1);
    
    floor->draw(kTextureGround, 15, 15);
    ceiling->draw(kTextureCeiling, 15, 15);
    exit->draw(kTextureDoor, 1, 1);
    
    if (!Game::isKeyFound())
        key->draw(kTextureKey, 1, 1);
    
    for (int i = 0; i < numOfObstacles; i++)
        obstacles[i]->draw();
}

// gameplay
bool Maze::isPointNearWall(Point *p) {
    for (int i = 0; i < numOfWalls; i++)
        if (walls[i]->intersectsPoint(p, 0.2))
            return true;
    
    return false;
}

bool Maze::isPointNearKey(Point *p) {
    return key->intersectsPoint(p, 0.25);
}

bool Maze::isPointNearExit(Point *p) {
    return exit->intersectsPoint(p, 1.0);
}

Obstacle * Maze::isPointNearObstacle(Point *p) {
    for (int i = 0; i < numOfObstacles; i++)
        if (obstacles[i]->intersectsPoint(p))
            return obstacles[i];
    
    return NULL;
}



