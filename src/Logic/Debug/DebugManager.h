#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

namespace sge{
    class DebugEntity;

    class DebugManager{
        public:
            void registerDebugEntity(sf::View* view, sge::DebugEntity* debugEntity);
            void registerDebugEntities(sf::View* view, std::vector<sge::DebugEntity*> debugEntities);
            void deregisterDebugEntity(sf::View* view, sge::DebugEntity* debugEntity);
            void deregisterAllDebugEntities();

            void showDebugInfo(sf::RenderWindow* windowPtr);

        private:
            std::unordered_map<sf::View*, std::vector<sge::DebugEntity*>> m_debugEntities;
    };
}


#endif