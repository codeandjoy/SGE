#ifndef SCENE_H
#define SCENE_H

#include <unordered_map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "../../Component/StatefulComponent.h"


namespace sge{
    class Entity;
    class DebugEntity;
    class CollisionShape;
    struct CollisionPair;

    class Scene : public sge::StatefulComponent{
        public:
            // rename to 'add' (parts are added)
            void addEntity(sf::View* view, sge::Entity* entity);
            void addEntities(sf::View* view, std::vector<sge::Entity*> entities);
            void addDebugEntity(sf::View* view, sge::DebugEntity* debugEntity);
            void addDebugEntities(sf::View* view, std::vector<sge::DebugEntity*> debugEntities);
        
            void activateSceneParts();
            void pauseSceneParts();
            void hideSceneParts();

        
            std::vector<sge::Entity*> getViewEntities(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::Entity*>> getEntitiesMap();

            std::vector<sge::DebugEntity*> getViewDebugEntities(sf::View* view);
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> getDebugEntitiesMap();
            
        private:
            // Hidden because extended using 'activateScene', 'pauseScene' and 'hideScene'
            using sge::StatefulComponent::activate;
            using sge::StatefulComponent::pause;
            using sge::StatefulComponent::hide;
            // 

            std::unordered_map<sf::View*, std::vector<sge::Entity*>> m_entities;
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> m_debugEntities;
    };
}


#endif