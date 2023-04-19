#include "EntityManager.h"

EntityManager::EntityManager(PhysicsManager* physicsManager, CollisionManager* collisionManager, TextureManager* textureManager){
    m_physicsManagerPtr = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_textureManagerPtr = textureManager;
}

void EntityManager::registerEntityGroup(std::string name, std::vector<Entity*> entityGroup){
    
    for(Entity* entity : entityGroup){
        m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
        
        if(entity->collisionShapes.size()){
            // Map to vector
            std::vector<CollisionShape*> entityCollisionShapes;
            for(auto& [_, collisionShape] : entity->collisionShapes){
                entityCollisionShapes.push_back(collisionShape);
            }
            //
            m_collisionManagerPtr->registerCollisionShapes(entityCollisionShapes);
        }
        
        if(entity->animation){
            m_textureManagerPtr->registerAnimation(entity->animation);
        }
    }


    m_entityGroups[name] = entityGroup;    
}

std::unordered_map<std::string, std::vector<Entity*>> EntityManager::getAllEntityGroups(){ return m_entityGroups; }

// TODO destroy
