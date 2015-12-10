//
//  Sticker.h
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#ifndef Sticker_h
#define Sticker_h

#include "Square.h"

class Sticker : public Square {
    
private:
    // drawing
    int textureIndex;
    
    // used for rotating
    int r, c;
    int orientation;
    bool rotating;
    
    // drawing
    void drawCoords(int row, int col);
    
public:
    // constructors
    Sticker();
    Sticker(int textureIndex, int r, int c);
    ~Sticker();
    
    // getters and setters
    int getTextureIndex();
    void setTextureIndex(int index);
    void setR(int r);
    void setC(int c);
    
    // rotating
    void rotate(int angle);
    
    // drawing
    void draw(int row, int col);
};

#endif 
