#ifndef ENTITY_H
#define ENTITY_H

#include "../../Component/StatefulComponent.h"


namespace sge{
    class Sprite;
    class PhysicalObject;
    class CollisionShape;
    class ClickableShape;
    class SpriteText;
    class Animation;
    class StateCluster;

    class Entity : public sge::StatefulComponent{
        public:
            sge::Sprite* sprite;
            sge::PhysicalObject* physicalObject = nullptr;
            std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
            sge::ClickableShape* clickableShape = nullptr;
            sge::SpriteText* spriteText = nullptr;
            sge::Animation* animation = nullptr;
            sge::StateCluster* stateCluster = nullptr;

            void activateEntity();
            void pauseEntity();
            void hideEntity();

        private:
            // Hidden because extended using 'activateEntity', 'pauseEntity' and 'hideEntity'
            using sge::StatefulComponent::activate;
            using sge::StatefulComponent::pause;
            using sge::StatefulComponent::hide;
            // 
    };
}


#endif