//
//  Sticker.cpp
//  RubixCube
//
//  Created by Cohen Adair on 2015-10-01.
//  Copyright © 2015 Cohen Adair. All rights reserved.
//

#include "Sticker.h"

// constructors
Sticker::Sticker() {
    
}

Sticker::Sticker(int textureIndex, int r, int c) : Square() {
    
    // sticker coordinates are all the same since they are all drawn in the same relative translation/rotation
    setTopRight(new Point(kStickerRadius - kStickerShrink, kStickerRadius - kStickerShrink, kStickerOffset));
    setTopLeft(new Point(-kStickerRadius + kStickerShrink, kStickerRadius - kStickerShrink, kStickerOffset));
    setBottomLeft(new Point(-kStickerRadius + kStickerShrink, -kStickerRadius + kStickerShrink, kStickerOffset));
    setBottomRight(new Point(kStickerRadius - kStickerShrink, -kStickerRadius + kStickerShrink, kStickerOffset));
    
    this->textureIndex = textureIndex;
    this->r = r;
    this->c = c;
    this->orientation = 0;
    this->rotating = false;
}

Sticker::~Sticker() {

}

// getters and setters
int Sticker::getTextureIndex() {
    return textureIndex;
}

void Sticker::setTextureIndex(int index) {
    textureIndex = index;
}

void Sticker::setR(int r) {
    this->r = r;
}

void Sticker::setC(int c) {
    this->c = c;
}

// rotating
void Sticker::rotate(int angle) {
    orientation = (orientation + angle) % 360;
    rotating = true;
}

// drawing
void Sticker::draw(int row, int col) {
    GLUtils::switchTexture(textureIndex);
    glColor3f(1, 1, 1);
    
    glPushMatrix();

        glTranslatef(-kCubeRadius + (kStickerSize * col) + kStickerRadius, kCubeRadius - (kStickerSize * row) - kStickerRadius, kCubeRadius);
        glColor3f(1, 1, 1);
        glRotatef(orientation, 0, 0, 1);
    
        glBegin(GL_QUADS);
        
            // bottom left
            glTexCoord2f(kPieceOffset(c), kPieceOffset(r) + kStickerSize);
            getBottomLeft()->draw();
            
            // bottom right
            glTexCoord2f(kPieceOffset(c) + kStickerSize, kPieceOffset(r) + kStickerSize);
            getBottomRight()->draw();
    
            // top right
            glTexCoord2f(kPieceOffset(c) + kStickerSize, kPieceOffset(r));
            getTopRight()->draw();
    
            // top left
            glTexCoord2f(kPieceOffset(c), kPieceOffset(r));
            getTopLeft()->draw();
    
        glEnd();
    
    glPopMatrix();
    
    rotating = false;
}
