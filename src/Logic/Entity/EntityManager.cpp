#include "EntityManager.h"
#include "Entity.h"
#include "../SpriteManager/SpriteManager.h"
#include "../Physics/PhysicsManager.h"
#include "../CollisionShape/CollisionShapeManager.h"
#include "../AnimationManager/AnimationManager.h"
#include "../Collision/CollisionManager.h"


sge::EntityManager::EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionShapeManager* collisionShapeManager, sge::AnimationManager* animationManager, sge::CollisionManager* collisionManager){
    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManager = collisionShapeManager;
    m_animationManagerPtr = animationManager;
    m_collisionManager = collisionManager;
}



void sge::EntityManager::registerEntity(sge::Entity* entity){
    m_spriteManagerPtr->registerSprite(entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->registerPhysicalObject(entity->physicalObject);
    }
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManager->registerCollisionShape(collisionShape);
        }
    }
    
    if(entity->animation){
        m_animationManagerPtr->registerAnimation(entity->animation);
    }

    m_entities.push_back(entity);
}

void sge::EntityManager::registerEntities(std::vector<sge::Entity*> entities){
    for(sge::Entity* entity : entities){
        registerEntity(entity);
    }
}

void sge::EntityManager::deregisterEntity(sge::Entity* entity){
    m_deregisterEntityFromCoreManagers(entity);

    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());    
}

void sge::EntityManager::deregisterAllEntities(){
    for(Entity* entity : m_entities){
        m_deregisterEntityFromCoreManagers(entity);
    }

    m_entities.clear();
}

std::vector<sge::Entity*> sge::EntityManager::getAllEntities(){ return m_entities; }



void sge::EntityManager::m_deregisterEntityFromCoreManagers(sge::Entity* entity){
    m_spriteManagerPtr->deregisterSprite(entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->deregisterPhysicalObject(entity->physicalObject);
    }

    if(entity->collisionShapes.size()){
        for(auto[_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManager->deregisterCollisionShape(collisionShape);
            m_collisionManager->deregisterCollisionShapeFromCollisionGroups(collisionShape);
        }
    }

    if(entity->animation){
        m_animationManagerPtr->deregisterAnimation(entity->animation);
    }
}