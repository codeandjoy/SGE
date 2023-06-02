#include "EntityManager.h"
#include "Entity.h"
#include "../Sprite/SpriteManager.h"
#include "../Physics/PhysicsManager.h"
#include "../CollisionShape/CollisionShapeManager.h"
#include "../ClickableShape/ClickableShapeManager.h"
#include "../SpriteText/SpriteTextManager.h"
#include "../State/StateManager.h"
#include "../Animation/AnimationManager.h"
#include "../Collision/CollisionManager.h"


sge::EntityManager::EntityManager(
        sge::SpriteManager* spriteManager,
        sge::PhysicsManager* physicsManager,
        sge::CollisionShapeManager* collisionShapeManager,
        sge::ClickableShapeManager* clickableShapeManager,
        sge::SpriteTextManager* spriteTextManager,
        sge::AnimationManager* animationManager,
        sge::StateManager* stateManager,
        sge::CollisionManager* collisionManager
    ){

    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManagerPtr = collisionShapeManager;
    m_clickableShapeManagerPtr = clickableShapeManager;
    m_spriteTextManagerPtr = spriteTextManager;
    m_animationManagerPtr = animationManager;
    m_stateManagerPtr = stateManager;
    m_collisionManagerPtr = collisionManager;
}



void sge::EntityManager::registerEntity(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->registerComponent(view, entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->registerComponent(entity->physicalObject);
    }
        
    if(entity->collisionShapes.size()){
        for(auto& [_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManagerPtr->registerComponent(collisionShape);
        }
    }

    if(entity->clickableShape){
        m_clickableShapeManagerPtr->registerComponent(view, entity->clickableShape);
    }

    if(entity->spriteText){
        m_spriteTextManagerPtr->registerComponent(view, entity->spriteText);
    }
    
    if(entity->animation){
        m_animationManagerPtr->registerComponent(entity->animation);
    }

    if(entity->stateCluster){
        m_stateManagerPtr->registerComponent(entity->stateCluster);
    }


    sge::ViewManager<sge::Entity*>::registerComponent(view, entity);
}

void sge::EntityManager::deregisterEntity(sf::View* view, sge::Entity* entity){
    m_spriteManagerPtr->deregisterComponent(view, entity->sprite);

    if(entity->physicalObject){
        m_physicsManagerPtr->deregisterComponent(entity->physicalObject);
    }

    if(entity->collisionShapes.size()){
        for(auto[_, collisionShape] : entity->collisionShapes){
            m_collisionShapeManagerPtr->deregisterComponent(collisionShape);
            m_collisionManagerPtr->deregisterCollisionShapeFromCollisionGroups(collisionShape);
        }
    }

    if(entity->clickableShape){
        m_clickableShapeManagerPtr->deregisterComponent(view, entity->clickableShape);
    }

    if(entity->spriteText){
        m_spriteTextManagerPtr->deregisterComponent(view, entity->spriteText);
    }

    if(entity->animation){
        m_animationManagerPtr->deregisterComponent(entity->animation);
    }

    if(entity->stateCluster){
        m_stateManagerPtr->deregisterComponent(entity->stateCluster);
    }


    sge::ViewManager<sge::Entity*>::deregisterComponent(view, entity);
}