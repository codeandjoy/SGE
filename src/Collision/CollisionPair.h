#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <SFML/Graphics.hpp> 
#include "Collision.h"
#include "CollisionShape.h"


struct CollisionPair{
    std::pair<std::string, std::string> collisionGroups;
    
    std::function<void(std::vector<Collision>)> startPhaseCollisionResponse;
    std::function<void(std::vector<Collision>)> continuousPhaseCollisionResponse;
    std::function<void(std::vector<Collision>)> endPhaseCollisionResponse;

    std::map<CollisionShape*, std::vector<Collision>> pastCollisions;
    
    std::function<bool(CollisionShape *initiator, CollisionShape *recipient)> checkCollision;
};


#endif