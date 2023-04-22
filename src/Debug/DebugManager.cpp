#include "DebugManager.h"
#include "DebugEntity.h"
#include "CollisionShapeBorder.h"


void DebugManager::registerDebugEntity(DebugEntity* debugEntity){ m_debugEntities.push_back(debugEntity); }



void DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(DebugEntity* debugEntity : m_debugEntities){
        // Run extraDebugFunctions
        for(std::function<void(sf::RenderWindow* renderWindow)> extraDebugFunction : debugEntity->getExtraDebugFunctions()){
            extraDebugFunction(windowPtr);
        }
        //

        // Draw collision shape borders
        if(debugEntity->drawCollisionShapeBorders){
            for(CollisionShapeBorder* collisionShapeBorder : debugEntity->generateCollisionShapeBorders()){
                windowPtr->draw(*collisionShapeBorder);
            }
        }
        //
    }
}