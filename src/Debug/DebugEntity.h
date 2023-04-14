#ifndef DEBUG_ENTITY_H
#define DEBUG_ENTITY_H

#include "../Entity/Entity.h"
#include "./CollisionShapeBorder.h"
#include "./CollisionShapeBorderSettings.h"


class DebugEntity{
    public:
        DebugEntity(Entity* relatedEntity);

        bool drawCollisionShapeBorders = true;
        std::map<std::string, CollisionShapeBorderSettings> customCollisionShapeBorderSettings;
        std::vector<CollisionShapeBorder*> generateCollisionShapeBorders();

        void addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction);
        std::vector<std::function<void(sf::RenderWindow* windowPtr)>> getExtraDebugFunctions();

    private:
        Entity* m_relatedEntity;
        CollisionShapeBorderSettings m_defaultCollisionShapeBorderSettings = CollisionShapeBorderSettings();
        std::vector<std::function<void(sf::RenderWindow* windowPtr)>> m_extraDebugFunctions;
};


#endif