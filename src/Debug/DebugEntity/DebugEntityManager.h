#ifndef DEBUG_ENTITY_MANAGER_H
#define DEBUG_ENTITY_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

#include "../../Structure/Manager/StorageManagers/ViewManager.h" 
#include "../../Structure/Manager/LoopSectionManagers/DrawManager.h" 


namespace sge{
    class DebugEntity;

    class DebugEntityManager :
        public sge::ViewManager<sge::DebugEntity*>,
        public sge::DrawManager{

        public:
            void draw(sf::RenderWindow* window) override;
    };
}


#endif