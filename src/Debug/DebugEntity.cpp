#include "DebugEntity.h"

DebugEntity::DebugEntity(Entity* relatedEntity){ m_relatedEntity = relatedEntity; }



std::vector<CollisionShapeBorder*> DebugEntity::generateCollisionShapeBorders(){
    std::vector<CollisionShapeBorder*> collisionShapeBorders;
    for(auto &[name, collisionShape] : m_relatedEntity->collisionShapes){
        if(customCollisionShapeBorderSettings.count(name)){
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, customCollisionShapeBorderSettings[name]));
        }
        else{
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, m_defaultCollisionShapeBorderSettings));
        }
    }

    return collisionShapeBorders;
}



void DebugEntity::addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction){ m_extraDebugFunctions.push_back(extraDebugFunction); }
std::vector<std::function<void(sf::RenderWindow* windowPtr)>> DebugEntity::getExtraDebugFunctions(){ return m_extraDebugFunctions; }