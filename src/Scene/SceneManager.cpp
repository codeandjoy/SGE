#include "SceneManager.h"
#include "Scene.h"
#include "../Physics/PhysicsManager.h"
#include "../Collision/CollisionManager.h"
#include "../Animation/AnimationManager.h"
#include "../Entity/EntityManager.h"
#include "../Debug/DebugManager.h"


sge::SceneManager::SceneManager(
        sge::PhysicsManager* physicsManager,
        sge::CollisionManager* collisionManager,
        sge::AnimationManager* animationManager,
        sge::EntityManager* entityManager,
        sge::DebugManager* debugManager
    ){
    
    m_physicsManagerPtr = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_animationManagerPtr = animationManager;
    m_entityManagerPtr = entityManager;
    m_debugManagerPtr = debugManager;
}



void sge::SceneManager::registerScene(std::string name, sge::Scene* scene){ m_scenes[name] = scene; }
void sge::SceneManager::setCurrentScene(std::string name){ m_currentScene = name; }
void sge::SceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            m_physicsManagerPtr->deregisterAllPhysicalObjects();
            m_collisionManagerPtr->deregisterAllCollisionShapes();
            m_collisionManagerPtr->deregisterAllCollisionGroups();
            m_collisionManagerPtr->deregisterAllCollisionPairs();
            m_animationManagerPtr->deregisterAllAnimations();
            m_entityManagerPtr->deregisterAllEntities();
            m_debugManagerPtr->deregisterAllDebugEntities();


            m_entityManagerPtr->registerEntities(m_scenes[m_currentScene]->getEntities());
            m_debugManagerPtr->registerDebugEntities(m_scenes[m_currentScene]->getDebugEntities());
            m_collisionManagerPtr->registerCollisionGroups(m_scenes[m_currentScene]->getCollisionGroups());
            m_collisionManagerPtr->registerCollisionPairs(m_scenes[m_currentScene]->getCollisionPairs());
            m_collisionManagerPtr->setCollisionPairsOrder(m_scenes[m_currentScene]->getCollisionPairsOrder());

            m_loadedScene = m_currentScene;
        }
    }
}