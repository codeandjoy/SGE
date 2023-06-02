#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>
#include "../Manager/StorageManagers/VectorManager.h"
#include "../Manager/LoopSectionManagers/EventManager.h"


namespace sge{
    class ControllerManager :
        public sge::VectorManager<std::function<void(sf::Event)>>,
        public sge::EventManager{

        public:
            void processEvent(sf::Event event) override;
    };
}


#endif