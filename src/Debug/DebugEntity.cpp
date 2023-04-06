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