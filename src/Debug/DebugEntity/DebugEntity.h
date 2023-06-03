#ifndef DEBUG_ENTITY_H
#define DEBUG_ENTITY_H

#include <SFML/Graphics.hpp> 
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

#include "../CollisionShapeBorder/CollisionShapeBorderSettings.h"
#include "../../Component/StatefulComponent.h"


namespace sge{
    class Entity;
    class CollisionShapeBorder;

    class DebugEntity : public sge::StatefulComponent{
        public:
            DebugEntity(sge::Entity* relatedEntity);

            sge::Entity* getRelatedEntity();

            bool drawCollisionShapeBorders = true;
            std::unordered_map<std::string, sge::CollisionShapeBorderSettings> customCollisionShapeBorderSettings;
            std::vector<sge::CollisionShapeBorder*> generateCollisionShapeBorders();

            void addExtraDebugFunction(std::function<void(sf::RenderWindow* windowPtr)> extraDebugFunction);
            std::vector<std::function<void(sf::RenderWindow* windowPtr)>> getExtraDebugFunctions();

        private:
            sge::Entity* m_relatedEntity;
            sge::CollisionShapeBorderSettings m_defaultCollisionShapeBorderSettings = sge::CollisionShapeBorderSettings();
            std::vector<std::function<void(sf::RenderWindow* windowPtr)>> m_extraDebugFunctions;
    };
}


#endif