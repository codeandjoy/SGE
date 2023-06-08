#include "SceneManager.h"
#include "Scene.h"
#include "../Entity/EntityManager.h"
#include "../Collision/CollisionManager.h"
#include "../../Debug/DebugManager.h"


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
}