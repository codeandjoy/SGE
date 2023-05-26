#include "DebugManager.h"
#include "DebugEntity.h"
#include "CollisionShapeBorder.h"


void sge::DebugManager::registerDebugEntity(sf::View* view, sge::DebugEntity* debugEntity){ m_debugEntities[view].push_back(debugEntity); }
void sge::DebugManager::registerDebugEntities(sf::View* view, std::vector<sge::DebugEntity*> debugEntities){
    for(DebugEntity* debugEntity : debugEntities){
        registerDebugEntity(view, debugEntity);
    }
}
void sge::DebugManager::deregisterDebugEntity(sf::View* view, sge::DebugEntity* debugEntity){ m_debugEntities[view].erase(std::remove(m_debugEntities[view].begin(), m_debugEntities[view].end(), debugEntity), m_debugEntities[view].end()); }
void sge::DebugManager::deregisterAllDebugEntities(){ m_debugEntities.clear(); }



void sge::DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(auto& [view, debugEntities]: m_debugEntities){
        for(sge::DebugEntity* debugEntity : debugEntities){
            // Run extraDebugFunctions
            for(std::function<void(sf::RenderWindow* renderWindow)> extraDebugFunction : debugEntity->getExtraDebugFunctions()){
                extraDebugFunction(windowPtr);
            }
            //

            // Draw collision shape borders
            if(debugEntity->drawCollisionShapeBorders){
                for(sge::CollisionShapeBorder* collisionShapeBorder : debugEntity->generateCollisionShapeBorders()){
                    windowPtr->setView(*view);
                    windowPtr->draw(*collisionShapeBorder);
                }
            }
            //
        }
    }
}