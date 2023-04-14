#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "../Physics/PhysicsManager.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"


class EntityManager{
    public:
        EntityManager(PhysicsManager* physicsManager, CollisionManager* collisionManager, TextureManager* textureManager);

        void registerEntityGroup(std::string name, std::vector<Entity*> entityGroup);
        std::map<std::string, std::vector<Entity*>> getAllEntityGroups();
        void destroyEntityGroup(std::string name);
        void destroyEntity(std::string memberEntityGroup, Entity* entity);

    private:
        std::map<std::string, std::vector<Entity*>> m_entityGroups;

        PhysicsManager* m_physicsManagerPtr;
        CollisionManager* m_collisionManagerPtr;
        TextureManager* m_textureManagerPtr;

};


#endif