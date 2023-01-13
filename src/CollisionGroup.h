#ifndef COLLISION_GROUP_H
#define COLLISION_GROUP_H

#include <SFML/Graphics.hpp>
#include "CollisionGroupType.h"


struct CollisionGroup{
    std::vector<sf::Sprite*> spriteVec;
    CollisionGroupType collisionGroupType;

    CollisionGroup(std::vector<sf::Sprite*> spriteVec_, CollisionGroupType collisionGroupType_){
        spriteVec = spriteVec_;
        collisionGroupType = collisionGroupType_;
    }
};


#endif COLLISION_GROUP_H