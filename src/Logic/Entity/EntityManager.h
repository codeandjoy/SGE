#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>


namespace sge{
    struct Entity;
    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class AnimationManager;
    class CollisionManager;

    class EntityManager{
        public:
            EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionShapeManager* collisionShapeManager, sge::AnimationManager* animationManager, sge::CollisionManager* collisionManager);


            void registerEntity(sf::View* view, sge::Entity* entity);
            void registerEntities(sf::View* view, std::vector<sge::Entity*> entities);
            void deregisterEntity(sf::View* view, sge::Entity* entity);
            void deregisterAllEntities();
            std::vector<sge::Entity*> getViewEntities(sf::View* view);

        private:
            std::unordered_map<sf::View*, std::vector<sge::Entity*>> m_entities;

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManager;
            sge::AnimationManager* m_animationManagerPtr;
            sge::CollisionManager* m_collisionManager;


            void m_deregisterEntityFromCoreManagers(sf::View* view, sge::Entity* entity);
    };
}


#endif