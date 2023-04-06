#include "DebugManager.h"

void DebugManager::registerDebugEntity(DebugEntity* de){ debugEntities.push_back(de); }

void DebugManager::showDebugInfo(sf::RenderWindow* windowPtr){
    for(DebugEntity* debugEntity : debugEntities){
        // Run extraDebugFunctions
        for(std::function<void(sf::RenderWindow* rw)> edf : debugEntity->getExtraDebugFunctions()){
            edf(windowPtr);
        }

        // Collision shape borders
        if(debugEntity->drawCollisionShapeBorders){
            for(CollisionShapeBorder* csb : debugEntity->generateCollisionShapeBorders()){
                windowPtr->draw(*csb);
            }
        }
    }
}