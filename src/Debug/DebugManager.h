#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>


namespace sge{
    class DebugEntity;

    class DebugManager{
        public:
            void registerDebugEntity(sge::DebugEntity* debugEntity);

            void showDebugInfo(sf::RenderWindow* windowPtr);

        private:
            std::vector<sge::DebugEntity*> m_debugEntities; // ? map<Entity -> DebugEntity> ?
    };
}


#endif