#include "DebugEntity.h"
#include "../../Logic/Entity/Entity.h"
#include "../CollisionShapeBorder/CollisionShapeBorder.h"


sge::DebugEntity::DebugEntity(sge::Entity* relatedEntity){ m_relatedEntity = relatedEntity; }



sge::Entity* sge::DebugEntity::getRelatedEntity(){ return m_relatedEntity; }



std::vector<sge::CollisionShapeBorder*> sge::DebugEntity::generateCollisionShapeBorders(){
    std::vector<sge::CollisionShapeBorder*> collisionShapeBorders;
    for(auto &[name, collisionShape] : m_relatedEntity->collisionShapes){
        if(customCollisionShapeBorderSettings.count(name)){
            collisionShapeBorders.push_back(new sge::CollisionShapeBorder(collisionShape, customCollisionShapeBorderSettings[name]));
        }
        else{
            collisionShapeBorders.push_back(new sge::CollisionShapeBorder(collisionShape, m_defaultCollisionShapeBorderSettings));
        }
    }

    return collisionShapeBorders;
}



void sge::DebugEntity::addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction){ m_extraDebugFunctions.push_back(extraDebugFunction); }
std::vector<std::function<void(sf::RenderWindow* windowPtr)>> sge::DebugEntity::getExtraDebugFunctions(){ return m_extraDebugFunctions; }