#include "EntityManager.h"
#include "Entity.h"
#include "../SpriteManager/SpriteManager.h"
#include "../Physics/PhysicsManager.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"


sge::EntityManager::EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionManager* collisionManager, sge::TextureManager* textureManager){
    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_textureManagerPtr = textureManager;
}


void sge::EntityManager::registerEntity(sge::Entity* entity){
    m_spriteManagerPtr->registerSprite(entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
    }
        
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

void sge::EntityManager::deregisterEntity(sge::Entity* entity){
    m_spriteManagerPtr->deregisterSprite(entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->deregisterPhysicalObject(entity->physicalObject);
    }

    if(entity->collisionShapes.size()){
        // map to vector
        std::vector<CollisionShape*> collisionShapes;
        for(auto[_, collisionShape] : entity->collisionShapes){
            collisionShapes.push_back(collisionShape);
        }
        //
        m_collisionManagerPtr->deregisterCollisionShapes(collisionShapes);
    }

    if(entity->animation){
        m_textureManagerPtr->deregisterAnimation(entity->animation);
    }

    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());    
}

void sge::EntityManager::deregisterAllEntities(){
    m_entities.clear();
}

std::vector<sge::Entity*> sge::EntityManager::getAllEntities(){ return m_entities; }