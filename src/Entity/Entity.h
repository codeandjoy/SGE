#ifndef ENTITY_H
#define ENTITY_H

#include "../Physics/PhysicalObject.h"
#include "../Collision/CollisionShape.h"
#include "../Texture/Animation.h"


struct Entity{
    PhysicalObject* physicalObject;
    std::map<std::string, CollisionShape*> collisionShapes; 
    Animation* animation = nullptr;
};


#endif