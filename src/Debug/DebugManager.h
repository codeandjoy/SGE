#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

class DebugEntity;


class DebugManager{
    public:
        void registerDebugEntity(DebugEntity* debugEntity);

        void showDebugInfo(sf::RenderWindow* windowPtr);

    private:
        std::vector<DebugEntity*> m_debugEntities; // ? map<Entity -> DebugEntity> ?
};


#endif