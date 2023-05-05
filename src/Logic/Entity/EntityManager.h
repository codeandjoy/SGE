#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>


namespace sge{
    class Entity;
    class SpriteManager;
    class PhysicsManager;
    class CollisionShapeManager;
    class AnimationManager;
    class CollisionManager;

    class EntityManager{
        public:
            EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionShapeManager* collisionShapeManager, sge::AnimationManager* animationManager, sge::CollisionManager* collisionManager);


            void registerEntity(sge::Entity* entity);
            void registerEntities(std::vector<sge::Entity*> entities);
            void deregisterEntity(sge::Entity* entity);
            void deregisterAllEntities();
            std::vector<sge::Entity*> getAllEntities();

        private:
            std::vector<sge::Entity*> m_entities;

            sge::SpriteManager* m_spriteManagerPtr;
            sge::PhysicsManager* m_physicsManagerPtr;
            sge::CollisionShapeManager* m_collisionShapeManager;
            sge::AnimationManager* m_animationManagerPtr;
            sge::CollisionManager* m_collisionManager;


            void m_deregisterEntityFromCoreManagers(sge::Entity* entity);
    };
}


#endif