#ifndef COLLISION_GROUP_H
#define COLLISION_GROUP_H

#include <SFML/Graphics.hpp>
#include "CollisionGroupType.h"
#include "CollisionShape.h"


struct CollisionGroup{
    CollisionGroupType collisionGroupType;
    std::vector<CollisionShape*> collisionShapes;
};


#endif