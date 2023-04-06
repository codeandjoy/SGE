#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include "./DebugEntity.h"


class DebugManager{
    public:
        void registerDebugEntity(DebugEntity* de);

        void showDebugInfo(sf::RenderWindow* windowPtr);

    private:
        std::vector<DebugEntity*> debugEntities;
};


#endif