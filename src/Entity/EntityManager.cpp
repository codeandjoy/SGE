#include "EntityManager.h"

EntityManager::EntityManager(PhysicsManager* _physicsManager, CollisionManager* _collisionManager, TextureManager* _textureManager){
    physicsManagerPtr = _physicsManager;
    collisionManagerPtr = _collisionManager;
    textureManagerPtr = _textureManager;
}

void EntityManager::registerEntityGroup(std::string name, std::vector<Entity*> _entityGroup){
    
    for(Entity* entity : _entityGroup){
        physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
        
        // Map to vector
        std::vector<CollisionShape*> entityCollisionShapes;
        for(auto& [_, collisionShape] : entity->collisionShapes){
            entityCollisionShapes.push_back(collisionShape);
        }
        //
        collisionManagerPtr->registerCollisionShapes(entityCollisionShapes);
        
        if(entity->animation){
            textureManagerPtr->registerAnimation(entity->animation);
        }
    }


    entityGroups[name] = _entityGroup;    
}

std::map<std::string, std::vector<Entity*>> EntityManager::getAllEntityGroups(){ return entityGroups; }

// TODO destroy
