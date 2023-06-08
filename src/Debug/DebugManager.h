#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

#include "../Manager/StorageManagers/ViewManager.h" 
#include "../Manager/LoopSectionManagers/DrawManager.h" 


namespace sge{
    class DebugEntity;

    class DebugManager :
        public sge::ViewManager<sge::DebugEntity*>,
        public sge::DrawManager{

        public:
            void draw(sf::RenderWindow* window) override;
    };
}


#endif