#include "SceneManager.h"
#include "Scene.h"
#include "../Physics/PhysicsManager.h"
#include "../Collision/CollisionManager.h"
#include "../Texture/TextureManager.h"
#include "../Entity/EntityManager.h"
#include "../Debug/DebugManager.h"


sge::SceneManager::SceneManager(
        sge::PhysicsManager* physicsManager,
        sge::CollisionManager* collisionManager,
        sge::TextureManager* textureManager,
        sge::EntityManager* entityManager,
        sge::DebugManager* debugManager
    ){
    
    m_physicsManager = physicsManager;
    m_collisionManagerPtr = collisionManager;
    m_textureManager = textureManager;
    m_entityManagerPtr = entityManager;
    m_debugManager = debugManager;
}



void sge::SceneManager::SceneManager::registerScene(std::string name, sge::Scene* scene){ m_scenes[name] = scene; }
void sge::SceneManager::loadScene(std::string name){
    m_physicsManager->deregisterAllPhysicalObjects();
    m_collisionManagerPtr->deregisterAllCollisionShapes();
    m_collisionManagerPtr->deregisterAllCollisionGroups();
    m_collisionManagerPtr->deregisterAllCollisionPairs();
    m_entityManagerPtr->deregisterAllEntities();
    m_debugManager->deregisterAllDebugEntities();


    m_entityManagerPtr->registerEntities(m_scenes[name]->getEntities());
    m_debugManager->registerDebugEntities(m_scenes[name]->getDebugEntities());
    m_collisionManagerPtr->registerCollisionGroups(m_scenes[name]->getCollisionGroups());
    m_collisionManagerPtr->registerCollisionPairs(m_scenes[name]->getCollisionPairs());
    m_collisionManagerPtr->setCollisionPairsOrder(m_scenes[name]->getCollisionPairsOrder());
}