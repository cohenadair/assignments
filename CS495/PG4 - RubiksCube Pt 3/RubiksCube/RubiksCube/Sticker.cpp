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
    
    backdrop = new Square();
    backdrop->setTopRight(new Point(kStickerRadius, kStickerRadius, 0));
    backdrop->setTopLeft(new Point(-kStickerRadius, kStickerRadius, 0));
    backdrop->setBottomLeft(new Point(-kStickerRadius, -kStickerRadius, 0));
    backdrop->setBottomRight(new Point(kStickerRadius, -kStickerRadius, 0));
    
    this->textureIndex = textureIndex;
    this->r = r;
    this->c = c;
    this->orientation = 0;
    this->rotating = false;
}

Sticker::~Sticker() {
    delete backdrop;
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
void Sticker::rotate(int angle, int animationAxis, int animationDirection) {
    orientation = (orientation + angle) % 360;
    rotating = true;
    this->animationAxis = animationAxis;
    this->animationDirection = animationDirection;
}

// drawing
void Sticker::draw(int row, int col, double animationAngle) {
    GLUtils::switchTexture(textureIndex);
    glColor3f(1, 1, 1);
    
    glPushMatrix();
    
        if (rotating) {
            int newAngle = animationAngle * animationDirection;
            GLUtils::rotateOnAxis(newAngle, animationAxis);
            
            // reset sticker rotation information
            if (animationAngle == 0)
                rotating = false;
        }

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
    
        // draw black background so you can't see through the cube
        glColor3f(0, 0, 0);
        backdrop->draw();
    
    glPopMatrix();
}
