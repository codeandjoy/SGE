#ifndef ENTITY_H
#define ENTITY_H


namespace sge{
    class PhysicalObject;
    class CollisionShape;
    class Animation;

    struct Entity{
        sf::Sprite* sprite;
        sge::PhysicalObject* physicalObject = nullptr;
        std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
        sge::Animation* animation = nullptr;
    };
}


#endif