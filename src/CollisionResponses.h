#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include "SFML/Graphics.hpp"
#include "PhysicalObject.h"


// ! Assuming PO1 is moveable
// TODO manage moveable and solid objects
void repel(PhysicalObject *physicalObject1, PhysicalObject *physicalObject2){
    float y1 = physicalObject1->getPosition().y;
    float x1 = physicalObject1->getPosition().x;
    float height1 = physicalObject1->getGlobalBounds().height;
    float width1 = physicalObject1->getGlobalBounds().width;
    float y2 = physicalObject2->getPosition().y;
    float x2 = physicalObject2->getPosition().x;
    float height2 = physicalObject2->getGlobalBounds().height;
    float width2 = physicalObject2->getGlobalBounds().width;

    bool btm = false, lt = false, rt = false; // Collision side flags

    // Bottom
    if(y1 + height1 > y2 && y1 + height1 < y2 + 1){
        physicalObject1->setPosition(physicalObject1->getPosition().x, y2 - height1);
        btm = true;
    }

    // Left
    if(x1 < x2 + width2 && x1 > x2 + width2 - 1 && btm == false){
        physicalObject1->setPosition(x2 + width2, physicalObject1->getPosition().y);
        lt = true;
    }

    // Right
    if(x1 + width1 > x2 && x1 + width1 < x2 + 1 && btm == false){
        physicalObject1->setPosition(x2 - width1, physicalObject1->getPosition().y);
        rt = true;
    }
}


#endif