#include "SceneManager.h"
#include "Scene.h"
#include "../SpriteManager/SpriteManager.h"
#include "../Physics/PhysicsManager.h"
#include "../CollisionShape/CollisionShapeManager.h"
#include "../AnimationManager/AnimationManager.h"
#include "../Collision/CollisionManager.h"
#include "../Entity/EntityManager.h"
#include "../../Debug/DebugManager/DebugManager.h"


sge::SceneManager::SceneManager(
        sge::SpriteManager* spriteManager,
        sge::PhysicsManager* physicsManager,
        sge::CollisionShapeManager* collisionShapeManager,
        sge::AnimationManager* animationManager,
        sge::CollisionManager* collisionManager,
        sge::EntityManager* entityManager
    ){
    
    
    m_spriteManagerPtr = spriteManager;
    m_physicsManagerPtr = physicsManager;
    m_collisionShapeManagerPtr = collisionShapeManager;
    m_animationManagerPtr = animationManager;
    m_collisionManagerPtr = collisionManager;
    m_entityManagerPtr = entityManager;
}



void sge::SceneManager::setupDebug(sge::DebugManager* debugManager){ m_debugManagerPtr = debugManager; }



void sge::SceneManager::registerScene(std::string name, sge::Scene* scene){ m_scenes[name] = scene; }
void sge::SceneManager::setCurrentScene(std::string name){ m_currentScene = name; }
void sge::SceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            m_entityManagerPtr->deregisterAllEntities();
            m_spriteManagerPtr->deregisterAllSprites();
            m_physicsManagerPtr->deregisterAllPhysicalObjects();
            m_collisionShapeManagerPtr->deregisterAllCollisionShapes();
            m_collisionManagerPtr->deregisterAllCollisionGroups();
            m_collisionManagerPtr->deregisterAllCollisionPairs();
            m_animationManagerPtr->deregisterAllAnimations();


            for(auto& [view, entities] : m_scenes[m_currentScene]->getEntitiesMap()){
                m_entityManagerPtr->registerEntities(view, entities);
            }
            m_collisionManagerPtr->registerCollisionGroups(m_scenes[m_currentScene]->getCollisionGroups());
            m_collisionManagerPtr->registerCollisionPairs(m_scenes[m_currentScene]->getCollisionPairs());
            m_collisionManagerPtr->setCollisionPairsOrder(m_scenes[m_currentScene]->getCollisionPairsOrder());


            if(m_debugManagerPtr){
                m_debugManagerPtr->deregisterAllDebugEntities();

                for(auto& [view, debugEntities] : m_scenes[m_currentScene]->getDebugEntitiesMap()){
                    m_debugManagerPtr->registerDebugEntities(view, debugEntities);
                }
            }


            m_loadedScene = m_currentScene;
        }
    }
}