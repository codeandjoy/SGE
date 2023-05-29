#include "EntityManager.h"
#include "Entity.h"
#include "../Sprite/SpriteManager.h"
#include "../Physics/PhysicsManager.h"
#include "../CollisionShape/CollisionShapeManager.h"
#include "../Animation/AnimationManager.h"
#include "../Collision/CollisionManager.h"


sge::EntityManager::EntityManager(sge::SpriteManager* spriteManager, sge::PhysicsManager* physicsManager, sge::CollisionShapeManager* collisionShapeManager, sge::AnimationManager* animationManager, sge::CollisionManager* collisionManager){
    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManager = collisionShapeManager;
    m_animationManagerPtr = animationManager;
    m_collisionManager = collisionManager;
}



void sge::EntityManager::registerEntity(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->registerSprite(view, entity->sprite);

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

    m_entities[view].push_back(entity);
}

void sge::EntityManager::registerEntities(sf::View* view, std::vector<sge::Entity*> entities){
    for(sge::Entity* entity : entities){
        registerEntity(view, entity);
    }
}

void sge::EntityManager::deregisterEntity(sf::View* view, sge::Entity* entity){
    m_deregisterEntityFromCoreManagers(view, entity);

    m_entities[view].erase(std::remove(m_entities[view].begin(), m_entities[view].end(), entity), m_entities[view].end());    
}

void sge::EntityManager::deregisterAllEntities(){
    for(auto& [view, entities] : m_entities){
        for(Entity* entity : entities){
            m_deregisterEntityFromCoreManagers(view, entity);
        }
    }

    m_entities.clear();
}

std::vector<sge::Entity*> sge::EntityManager::getViewEntities(sf::View* view){ return m_entities[view]; }



void sge::EntityManager::m_deregisterEntityFromCoreManagers(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->deregisterSprite(view, entity->sprite);

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