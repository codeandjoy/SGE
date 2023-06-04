#include "Scene.h"
#include "../Entity/Entity.h"
#include "../../Debug/DebugEntity/DebugEntity.h"


void sge::Scene::addEntity(sf::View* view, sge::Entity* entity){ m_entities[view].push_back(entity); }
void sge::Scene::addEntities(sf::View* view, std::vector<sge::Entity*> entities){
    for(Entity* entity : entities){
        addEntity(view, entity);
    }
}
void sge::Scene::addDebugEntity(sf::View* view, sge::DebugEntity* debugEntity){ m_debugEntities[view].push_back(debugEntity); }
void sge::Scene::addDebugEntities(sf::View* view,std::vector<DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        addDebugEntity(view, debugEntity);
    }
}
void sge::Scene::addCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionShapes){ m_collisionGroups[name] = collisionShapes; }
void sge::Scene::addCollisionPair(std::string name, sge::CollisionPair* collisionPair){
    m_collisionPairs[name] = collisionPair;
    m_collisionPairsOrder.push_back(name);
}


void sge::Scene::activateSceneParts(){
    for(auto& [_, entities] : m_entities){
        for(sge::Entity* entity : entities){
            entity->activateEntityParts();
        }
    }
    for(auto& [_, debugEntities] : m_debugEntities){
        for(sge::DebugEntity* debugEntity : debugEntities){
            debugEntity->activate();
        }
    }

    sge::StatefulComponent::activate();
}
void sge::Scene::pauseSceneParts(){
    for(auto& [_, entities] : m_entities){
        for(sge::Entity* entity : entities){
            entity->pauseEntityParts();
        }
    }
    for(auto& [_, debugEntities] : m_debugEntities){
        for(sge::DebugEntity* debugEntity : debugEntities){
            debugEntity->pause();
        }
    }

    sge::StatefulComponent::pause();
}
void sge::Scene::hideSceneParts(){
    for(auto& [_, entities] : m_entities){
        for(sge::Entity* entity : entities){
            entity->hideEntityParts();
        }
    }
    for(auto& [_, debugEntities] : m_debugEntities){
        for(sge::DebugEntity* debugEntity : debugEntities){
            debugEntity->hide();
        }
    }

    sge::StatefulComponent::hide();
}


std::vector<sge::Entity*> sge::Scene::getViewEntities(sf::View* view){ return m_entities[view]; }
std::unordered_map<sf::View*, std::vector<sge::Entity*>> sge::Scene::getEntitiesMap(){ return m_entities; };


std::vector<sge::DebugEntity*> sge::Scene::getViewDebugEntities(sf::View* view){ return m_debugEntities[view]; }
std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> sge::Scene::getDebugEntitiesMap(){ return m_debugEntities; }


std::unordered_map<std::string, std::vector<sge::CollisionShape*>> sge::Scene::getCollisionGroups(){ return m_collisionGroups; };
std::unordered_map<std::string, sge::CollisionPair*> sge::Scene::getCollisionPairs(){ return m_collisionPairs; }
std::vector<std::string> sge::Scene::getCollisionPairsOrder(){ return m_collisionPairsOrder; };