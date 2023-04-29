#include "Scene.h"


void sge::Scene::registerEntity(sge::Entity* entity){ m_entities.push_back(entity); }
void sge::Scene::registerEntities(std::vector<sge::Entity*> entities){
    for(Entity* entity : entities){
        registerEntity(entity);
    }
}
void sge::Scene::registerDebugEntity(sge::DebugEntity* debugEntity){ m_debugEntities.push_back(debugEntity); }
void sge::Scene::registerDebugEntities(std::vector<DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        registerDebugEntity(debugEntity);
    }
}
void sge::Scene::registerCollisionGroup(std::string name, std::vector<sge::CollisionShape*> collisionShapes){ m_collisionGroups[name] = collisionShapes; }
void sge::Scene::registerCollisionPair(std::string name, sge::CollisionPair* collisionPair){
    m_collisionPairs[name] = collisionPair;
    m_collisionPairsOrder.push_back(name);
}

std::vector<sge::Entity*> sge::Scene::getEntities(){ return m_entities; }
std::vector<sge::DebugEntity*> sge::Scene::getDebugEntities(){ return m_debugEntities; }
std::unordered_map<std::string, std::vector<sge::CollisionShape*>> sge::Scene::getCollisionGroups(){ return m_collisionGroups; };
std::unordered_map<std::string, sge::CollisionPair*> sge::Scene::getCollisionPairs(){ return m_collisionPairs; }
std::vector<std::string> sge::Scene::getCollisionPairsOrder(){ return m_collisionPairsOrder; };