#ifndef COLLISION_GROUP_H
#define COLLISION_GROUP_H

#include <SFML/Graphics.hpp>
#include "CollisionGroupType.h"
#include "CollisionShape.h"
#include "../Entity/Entity.h" 


struct CollisionGroup{
    CollisionGroupType collisionGroupType;
    std::vector<CollisionShape*> collisionShapes;
    std::vector<Entity*> ownerEntities;
};


#endif