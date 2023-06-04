#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
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
            sge::Sprite* sprite = nullptr;
            sge::PhysicalObject* physicalObject = nullptr;
            std::unordered_map<std::string, sge::CollisionShape*> collisionShapes; 
            sge::ClickableShape* clickableShape = nullptr;
            sge::SpriteText* spriteText = nullptr;
            sge::Animation* animation = nullptr;
            sge::StateCluster* stateCluster = nullptr;

            void activateEntityParts();
            void pauseEntityParts();
            void hideEntityParts();

        private:
            // Hidden because extended using 'activateEntityParts', 'pauseEntityParts' and 'hideEntityParts'
            using sge::StatefulComponent::activate;
            using sge::StatefulComponent::pause;
            using sge::StatefulComponent::hide;
            // 
    };
}


#endif