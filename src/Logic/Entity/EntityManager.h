#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

#include "../../Manager/StorageManagers/ViewManager.h"


namespace sge{
    class Entity;
    class SpriteManager;
    class MotionUnitManager;
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
                sge::MotionUnitManager* motionUnitManager,
                sge::CollisionShapeManager* collisionShapeManager,
                sge::ClickableShapeManager* clickableShapeManager,
                sge::SpriteTextManager* SpriteTextManager,
                sge::AnimationManager* animationManager,
                sge::StateManager* stateManager
            );

        void registerComponent(sf::View* view, sge::Entity* entity);
        void deregisterComponent(sf::View* view, sge::Entity* entity);


        private:
            // Hidden because extended
            using sge::ViewManager<sge::Entity*>::registerComponent;
            using sge::ViewManager<sge::Entity*>::deregisterComponent;
            //

            void m_registerEntityMembers(sf::View* view, sge::Entity* entity);
            void m_deregisterEntityMembers(sf::View* view, sge::Entity* entity);

            sge::SpriteManager* m_spriteManagerPtr;
            sge::MotionUnitManager* m_motionUnitManager;
            sge::CollisionShapeManager* m_collisionShapeManagerPtr;
            sge::ClickableShapeManager* m_clickableShapeManagerPtr;
            sge::SpriteTextManager* m_spriteTextManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;
            sge::StateManager* m_stateManagerPtr;
    };
}


#endif