#ifndef ENTITY_H
#define ENTITY_H


namespace sge{
    class Sprite;
    class PhysicalObject;
    class CollisionShape;
    class ClickableShape;
    class SpriteText;
    class Animation;
    class StateCluster;

    struct Entity{
        sge::Sprite* sprite;
        sge::PhysicalObject* physicalObject = nullptr;
        std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
        sge::ClickableShape* clickableShape = nullptr;
        sge::SpriteText* spriteText = nullptr;
        sge::Animation* animation = nullptr;
        sge::StateCluster* stateCluster = nullptr;
    };
}


#endif