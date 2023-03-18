#ifndef COLLISION_PAIR_H
#define COLLISION_PAIR_H

#include <SFML/Graphics.hpp> 
#include "../PhysicsManager/PhysicalObject.h"
#include "Collision.h"


// ? add collision type specifier (rectangle, circle etc.)
struct CollisionPair{
    std::tuple<std::string, std::string> collisionGroups;
    std::vector<std::function<void(std::vector<Collision>)>> collisionResponses; // TODO allow function with and without parameters (struct || simply register different types of functions and use the one that exists (or all of them))
    std::function<bool(PhysicalObject *PO1, PhysicalObject *PO2)> checkCollision;
};


#endif