#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
class Entity;
class PhysicsManager;
class CollisionManager;
class TextureManager;


class EntityManager{
    public:
        EntityManager(PhysicsManager* physicsManager, CollisionManager* collisionManager, TextureManager* textureManager);

        void registerEntity(Entity* entity);
        void registerEntities(std::vector<Entity*> entities);
        // void destroyEntity(Entity* entity);
        std::vector<Entity*> getAllEntities();

    private:
        std::vector<Entity*> m_entities;

        PhysicsManager* m_physicsManagerPtr;
        CollisionManager* m_collisionManagerPtr;
        TextureManager* m_textureManagerPtr;

};


#endif