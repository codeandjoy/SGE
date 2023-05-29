#include "SceneManager.h"
#include "Scene.h"
#include "../Entity/EntityManager.h"
#include "../Collision/CollisionManager.h"
#include "../../Debug/DebugManager/DebugManager.h"


sge::SceneManager::SceneManager(sge::EntityManager* entityManager, sge::CollisionManager* collisionManager){
    m_collisionManagerPtr = collisionManager;
    m_entityManagerPtr = entityManager;
}


void sge::SceneManager::setupDebug(sge::DebugManager* debugManager){ m_debugManagerPtr = debugManager; }


void sge::SceneManager::registerScene(std::string name, sge::Scene* scene){ m_scenes[name] = scene; }
void sge::SceneManager::setCurrentScene(std::string name){ m_currentScene = name; }
void sge::SceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            // Reset
            for(auto& [view, entities] : m_scenes[m_loadedScene]->getEntitiesMap()){
                m_entityManagerPtr->deregisterEntities(view, entities);
            }
            //

            // Register new scene members
            for(auto& [view, entities] : m_scenes[m_currentScene]->getEntitiesMap()){
                m_entityManagerPtr->registerEntities(view, entities);
            }
            m_collisionManagerPtr->registerCollisionGroups(m_scenes[m_currentScene]->getCollisionGroups());
            m_collisionManagerPtr->registerCollisionPairs(m_scenes[m_currentScene]->getCollisionPairs());
            m_collisionManagerPtr->setCollisionPairsOrder(m_scenes[m_currentScene]->getCollisionPairsOrder());
            //

            // Register debug members
            if(m_debugManagerPtr){
                m_debugManagerPtr->deregisterAllDebugEntities();

                for(auto& [view, debugEntities] : m_scenes[m_currentScene]->getDebugEntitiesMap()){
                    m_debugManagerPtr->registerDebugEntities(view, debugEntities);
                }
            }
            //

            m_loadedScene = m_currentScene;
        }
    }
}