#ifndef COLLISION_GROUP_H
#define COLLISION_GROUP_H

#include <SFML/Graphics.hpp>
#include "CollisionGroupType.h"


struct CollisionGroup{
    CollisionGroupType collisionGroupType;
    std::vector<sf::Sprite*> spriteVec;
};


#endif