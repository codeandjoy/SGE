#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>
#include "../Structure/Manager/StorageManagers/VectorManager.h"
#include "../Structure/Manager/LoopSectionManagers/EventManager.h"


namespace sge{
    class Controller;

    class ControllerManager :
        public sge::VectorManager<sge::Controller*>,
        public sge::EventManager{

        public:
            void processEvent(sf::Event event) override;
    };
}


#endif