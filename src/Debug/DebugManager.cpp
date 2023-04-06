#include "DebugManager.h"

void DebugManager::registerDebugEntity(DebugEntity* de){ debugEntities.push_back(de); }

void DebugManager::drawDebugInfo(sf::RenderWindow* windowPtr){
    for(DebugEntity* debugEntity : debugEntities){
        if(debugEntity->drawCollisionShapeBorders){
            for(CollisionShapeBorder* csb : debugEntity->generateCollisionShapeBorders()){
                windowPtr->draw(*csb);
            }
        }
    }
}