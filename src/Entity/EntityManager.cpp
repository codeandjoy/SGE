#include "EntityManager.h"
#include "Entity.h"
#include "../Physics/PhysicsManager.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"


sge::EntityManager::EntityManager(sge::PhysicsManager* physicsManager, sge::CollisionManager* collisionManager, sge::TextureManager* textureManager){
    m_physicsManagerPtr = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_textureManagerPtr = textureManager;
}


void sge::EntityManager::registerEntity(sge::Entity* entity){
    m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionManagerPtr->registerCollisionShape(collisionShape);
        }
    }
    
    if(entity->animation){
        m_textureManagerPtr->registerAnimation(entity->animation);
    }

    m_entities.push_back(entity);
}

void sge::EntityManager::registerEntities(std::vector<sge::Entity*> entities){
    for(sge::Entity* entity : entities){
        registerEntity(entity);
    }
}

std::vector<sge::Entity*> sge::EntityManager::getAllEntities(){ return m_entities; }