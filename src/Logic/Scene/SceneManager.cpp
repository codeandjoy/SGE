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


void sge::SceneManager::m_registerSceneMembers(std::string label){
    for(auto& [view, entities] : m_components[label]->getEntitiesMap()){
        for(sge::Entity* entity : entities){
            m_entityManagerPtr->registerComponent(view, entity);
        }
    }

    if(m_debugManagerPtr){
        for(auto& [view, debugEntities] : m_components[label]->getDebugEntitiesMap()){
            for(sge::DebugEntity* debugEntity : debugEntities){
                m_debugManagerPtr->registerComponent(view, debugEntity);
            }
        }
    }

    m_collisionManagerPtr->registerCollisionGroups(m_components[label]->getCollisionGroups());
    m_collisionManagerPtr->registerCollisionPairs(m_components[label]->getCollisionPairs());
    m_collisionManagerPtr->setCollisionPairsOrder(m_components[label]->getCollisionPairsOrder());
}

void sge::SceneManager::m_deregisterSceneMembers(std::string label){
    if(m_debugManagerPtr){
        for(auto& [view, debugEntities] : m_components[label]->getDebugEntitiesMap()){
            for(sge::DebugEntity* debugEntity : debugEntities){
                m_debugManagerPtr->deregisterComponent(view, debugEntity);
            }
        }
    }

    for(auto& [view, entities] : m_components[label]->getEntitiesMap()){
        for(sge::Entity* entity : entities){
            m_entityManagerPtr->deregisterComponent(view, entity);
        }
    }

    for(auto& [name, _] : m_components[label]->getCollisionGroups()){
        m_collisionManagerPtr->deregisterCollisionGroup(name);
    }
    // * Collision pairs and order gets auto removed
}