#ifndef DEBUG_ENTITY_H
#define DEBUG_ENTITY_H

#include "../Entity/Entity.h"
#include "./CollisionShapeBorder.h"
#include "./CollisionShapeBorderSettings.h"


class DebugEntity{
    public:
        DebugEntity(Entity* _relatedEntity);

        bool drawCollisionShapeBorders = true;
        std::map<std::string, CollisionShapeBorderSettings> customCollisionShapeBorderSettings;

        std::vector<CollisionShapeBorder*> generateCollisionShapeBorders();

    private:
        Entity* relatedEntity;

        CollisionShapeBorderSettings defaultCollisionShapeBorderSettings = CollisionShapeBorderSettings();
};


#endif