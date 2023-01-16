#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include "SFML/Graphics.hpp"


void repel(sf::Sprite *sprite1, sf::Sprite *sprite2){
    float y1 = sprite1->getPosition().y;
    float height1 = sprite1->getGlobalBounds().height;
    float y2 = sprite2->getPosition().y;
    float height2 = sprite2->getGlobalBounds().height;

    if(y1 + height1 > y2){
        sprite1->setPosition(sprite1->getPosition().x, y2-height1);
    }

    printf("%f\n", sprite1->getPosition().y);
    printf("%f\n", sprite1->getGlobalBounds().height);
    printf("%f\n", sprite2->getPosition().y);
    // the one that's moveable should change it's position to the 'outside' of solid one
        //      determine side on which collision occurred
        //      determine offset
        //      change moveable sprite's offset accordingly
}


#endif