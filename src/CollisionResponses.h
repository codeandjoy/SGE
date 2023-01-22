#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include "SFML/Graphics.hpp"


void repel(sf::Sprite *sprite1, sf::Sprite *sprite2){
    float y1 = sprite1->getPosition().y;
    float x1 = sprite1->getPosition().x;
    float height1 = sprite1->getGlobalBounds().height;
    float width1 = sprite1->getGlobalBounds().width;
    float y2 = sprite2->getPosition().y;
    float x2 = sprite2->getPosition().x;
    float height2 = sprite2->getGlobalBounds().height;
    float width2 = sprite2->getGlobalBounds().width;

    bool btm = false, lt = false, rt = false; // Collision side flags

    // Bottom
    if(y1 + height1 > y2 && y1 + height1 < y2 + 1){
        sprite1->setPosition(sprite1->getPosition().x, y2 - height1);
        btm = true;
    }

    // Left
    if(x1 < x2 + width2 && x1 > x2 + width2 - 1 && btm == false){
        sprite1->setPosition(x2 + width2, sprite1->getPosition().y);
        lt = true;
    }

    // Right
    if(x1 + width1 > x2 && x1 + width1 < x2 + 1 && btm == false){
        sprite1->setPosition(x2 - width1, sprite1->getPosition().y);
        rt = true;
    }
}


#endif