#include "ControllerManager.h"

void sge::ControllerManager::registerController(std::function<void(sf::Event)> controller){ m_controllers.push_back(controller); }
std::vector<std::function<void(sf::Event)>> sge::ControllerManager::getAllControllers(){ return m_controllers; }


void sge::ControllerManager::updateControllers(sf::Event event){
    for(std::function<void(sf::Event)> controller : m_controllers){
        controller(event);
    }
}