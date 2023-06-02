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


void sge::SceneManager::setCurrentScene(std::string name){ m_currentScene = name; }
void sge::SceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            // Reset previous scene members
            if(m_debugManagerPtr){
                for(auto& [view, debugEntities] : m_components[m_loadedScene]->getDebugEntitiesMap()){
                    for(sge::DebugEntity* debugEntity : debugEntities){
                        m_debugManagerPtr->deregisterComponent(view, debugEntity);
                    }
                }
            }

            for(auto& [view, entities] : m_components[m_loadedScene]->getEntitiesMap()){
                for(sge::Entity* entity : entities){
                    m_entityManagerPtr->deregisterEntity(view, entity);
                }
            }

            for(auto& [name, _] : m_components[m_loadedScene]->getCollisionGroups()){
                m_collisionManagerPtr->deregisterCollisionGroup(name);
            }
            // * Collision pairs and order gets auto removed
            //


            // Register new scene members
            for(auto& [view, entities] : m_components[m_currentScene]->getEntitiesMap()){
                for(sge::Entity* entity : entities){
                    m_entityManagerPtr->registerEntity(view, entity);
                }
            }

            if(m_debugManagerPtr){
                for(auto& [view, debugEntities] : m_components[m_currentScene]->getDebugEntitiesMap()){
                    for(sge::DebugEntity* debugEntity : debugEntities){
                        m_debugManagerPtr->registerComponent(view, debugEntity);
                    }
                }
            }
    
            m_collisionManagerPtr->registerCollisionGroups(m_components[m_currentScene]->getCollisionGroups());
            m_collisionManagerPtr->registerCollisionPairs(m_components[m_currentScene]->getCollisionPairs());
            m_collisionManagerPtr->setCollisionPairsOrder(m_components[m_currentScene]->getCollisionPairsOrder());
            //


            m_loadedScene = m_currentScene;
        }
    }
}