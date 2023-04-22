#ifndef ENTITY_H
#define ENTITY_H

class PhysicalObject;
class CollisionShape;
class Animation;


struct Entity{
    PhysicalObject* physicalObject;
    std::unordered_map<std::string, CollisionShape*> collisionShapes; 
    Animation* animation = nullptr;
};


#endif