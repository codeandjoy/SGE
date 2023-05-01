#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>


namespace sge{
    class Entity;
    class SpriteManager;
    class PhysicsManager;
    class CollisionManager;
    class AnimationManager;

    class EntityManager{
        public:
            EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionManager* collisionManager, sge::AnimationManager* animationManager);

            void registerEntity(sge::Entity* entity);
            void registerEntities(std::vector<sge::Entity*> entities);
            void deregisterEntity(sge::Entity* entity);
            void deregisterAllEntities();
            std::vector<sge::Entity*> getAllEntities();

        private:
            std::vector<sge::Entity*> m_entities;

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionManager* m_collisionManagerPtr;
            sge::AnimationManager* m_animationManagerPtr;

    };
}


#endif