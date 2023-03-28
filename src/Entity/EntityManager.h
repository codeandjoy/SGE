#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "../Physics/PhysicsManager.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"


class EntityManager{
    public:
        EntityManager(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager);

        void registerEntityGroup(std::string name, std::vector<Entity*> _entityGroup);
        std::map<std::string, std::vector<Entity*>> getAllEntityGroups();
        void destroyEntityGroup(std::string name);
        void destroyEntity(std::string memberEntityGroup, Entity* entity);

    private:
        std::map<std::string, std::vector<Entity*>> entityGroups;

        PhysicsManager* physicsManagerPtr;
        CollisionManager* collisionManagerPtr;
        TextureManager* textureManagerPtr;

};


#endif