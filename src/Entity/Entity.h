#ifndef ENTITY_H
#define ENTITY_H


namespace sge{
    class PhysicalObject;
    class CollisionShape;
    class Animation;

    struct Entity{
        sge::PhysicalObject* physicalObject;
        std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
        sge::Animation* animation = nullptr;
    };
}


#endif