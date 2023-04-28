#include "DebugManager.h"
#include "DebugEntity.h"
#include "CollisionShapeBorder.h"


void sge::DebugManager::registerDebugEntity(sge::DebugEntity* debugEntity){ m_debugEntities.push_back(debugEntity); }
void sge::DebugManager::registerDebugEntities(std::vector<sge::DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        registerDebugEntity(debugEntity);
    }
}
void sge::DebugManager::deregisterDebugEntity(sge::DebugEntity* debugEntity){ m_debugEntities.erase(std::remove(m_debugEntities.begin(), m_debugEntities.end(), debugEntity), m_debugEntities.end()); }
void sge::DebugManager::deregisterAllDebugEntities(){ m_debugEntities.clear(); }



void sge::DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(sge::DebugEntity* debugEntity : m_debugEntities){
        // Run extraDebugFunctions
        for(std::function<void(sf::RenderWindow* renderWindow)> extraDebugFunction : debugEntity->getExtraDebugFunctions()){
            extraDebugFunction(windowPtr);
        }
        //

        // Draw collision shape borders
        if(debugEntity->drawCollisionShapeBorders){
            for(sge::CollisionShapeBorder* collisionShapeBorder : debugEntity->generateCollisionShapeBorders()){
                windowPtr->draw(*collisionShapeBorder);
            }
        }
        //
    }
}