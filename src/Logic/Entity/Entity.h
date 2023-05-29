#ifndef ENTITY_H
#define ENTITY_H


namespace sge{
    class PhysicalObject;
    class CollisionShape;
    class ClickableShape;
    class SpriteText;
    class Animation;

    struct Entity{
        sf::Sprite* sprite;
        sge::PhysicalObject* physicalObject = nullptr;
        std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
        sge::ClickableShape* clickableShape;
        sge::SpriteText* spriteText;
        sge::Animation* animation = nullptr;
    };
}


#endif