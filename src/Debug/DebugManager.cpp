#include "DebugManager.h"
#include "DebugEntity.h"
#include "./CollisionShapeBorder/CollisionShapeBorder.h"


void sge::DebugManager::draw(sf::RenderWindow* window){
    for(auto& [view, debugEntities]: m_components){
        window->setView(*view);
        
        for(sge::DebugEntity* debugEntity : debugEntities){
            if(debugEntity->isActive || debugEntity->isPaused){
                // Run extraDebugFunctions
                // !
                // ! rewrite into update or just remove
                // !
                for(std::function<void(sf::RenderWindow* renderWindow)> extraDebugFunction : debugEntity->getExtraDebugFunctions()){
                    extraDebugFunction(window);
                }
                //

                // Draw collision shape borders
                if(debugEntity->drawCollisionShapeBorders){
                    for(sge::CollisionShapeBorder* collisionShapeBorder : debugEntity->generateCollisionShapeBorders()){
                        window->draw(*collisionShapeBorder);
                    }
                }
                //
            }
        }
    }
}