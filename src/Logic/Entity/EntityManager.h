#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Manager/StorageManagers/ViewManager.h"


namespace sge{
    class Entity;
    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class ClickableShapeManager;
    class SpriteTextManager;
    class AnimationManager;
    class CollisionManager;
    class StateManager;


    class EntityManager : public sge::ViewManager<sge::Entity*>{
        public:
            EntityManager(
                sge::SpriteManager* spriteManager,
                sge::PhysicsManager* physicsManager,
                sge::CollisionShapeManager* collisionShapeManager,
                sge::ClickableShapeManager* clickableShapeManager,
                sge::SpriteTextManager* SpriteTextManager,
                sge::AnimationManager* animationManager,
                sge::StateManager* stateManager,
                sge::CollisionManager* collisionManager
            );

        void registerEntity(sf::View* view, sge::Entity* entity);
        void deregisterEntity(sf::View* view, sge::Entity* entity);


        private:
            // Hidden because extended using 'registerEntiy' and 'deregisterEntity'
            using sge::ViewManager<sge::Entity*>::registerComponent;
            using sge::ViewManager<sge::Entity*>::deregisterComponent;
            //

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManagerPtr;
            sge::ClickableShapeManager* m_clickableShapeManagerPtr;
            sge::SpriteTextManager* m_spriteTextManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::StateManager* m_stateManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;
    };
}


#endif