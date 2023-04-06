#include "DebugEntity.h"

DebugEntity::DebugEntity(Entity* _relatedEntity){ relatedEntity = _relatedEntity; }

std::vector<CollisionShapeBorder*> DebugEntity::generateCollisionShapeBorders(){
    std::vector<CollisionShapeBorder*> collisionShapeBorders;

    for(auto &[name, collisionShape] : relatedEntity->collisionShapes){
        if(customCollisionShapeBorderSettings.count(name)){
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, customCollisionShapeBorderSettings[name]));
        }
        else{
            collisionShapeBorders.push_back(new CollisionShapeBorder(collisionShape, defaultCollisionShapeBorderSettings));
        }
    }

    return collisionShapeBorders;
}

void DebugEntity::addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> edf){ extraDebugFunctions.push_back(edf); }

std::vector<std::function<void(sf::RenderWindow* windowPtr)>> DebugEntity::getExtraDebugFunctions(){ return extraDebugFunctions; }