#include "EntityManager.h"

EntityManager::EntityManager(PhysicsManager* physicsManager, CollisionManager* collisionManager, TextureManager* textureManager){
    m_physicsManagerPtr = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_textureManagerPtr = textureManager;
}


void EntityManager::registerEntity(Entity* entity){
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

void EntityManager::registerEntities(std::vector<Entity*> entities){
    for(Entity* entity : entities){
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

        m_entities.push_back(entity);
    }
}

std::vector<Entity*> EntityManager::getAllEntities(){ return m_entities; }