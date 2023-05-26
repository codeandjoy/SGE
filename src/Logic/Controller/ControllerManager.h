#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <functional>
#include <vector>

#include <SFML/Graphics.hpp>


namespace sge{
    class ControllerManager{
        public:
            void registerController(std::function<void(sf::Event)> controller);
            std::vector<std::function<void(sf::Event)>> getAllControllers();       

            void updateControllers(sf::Event event);
            
        private:
            std::vector<std::function<void(sf::Event)>> m_controllers;
    };
}


#endif