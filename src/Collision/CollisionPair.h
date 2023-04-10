#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <SFML/Graphics.hpp> 
#include "Collision.h"
#include "CollisionShape.h"


struct CollisionPair{
    std::pair<std::string, std::string> collisionGroups;
    std::vector<std::function<void(std::vector<Collision>)>> collisionResponses;
    std::function<bool(CollisionShape *initiator, CollisionShape *recipient)> checkCollision;
};


#endif