#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "../Physics/PhysicsManager.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"


class EntityManager{
    public:
        EntityManager(PhysicsManager* physicsManager, CollisionManager* collisionManager, TextureManager* textureManager);

        void registerEntity(Entity* entity);
        void registerEntities(std::vector<Entity*> entities);
        void destroyEntity(Entity* entity);
        // void destroyEntityGroup(std::string name);
        std::vector<Entity*> getAllEntities();

    private:
        std::vector<Entity*> m_entities;

        PhysicsManager* m_physicsManagerPtr;
        CollisionManager* m_collisionManagerPtr;
        TextureManager* m_textureManagerPtr;

};


#endif