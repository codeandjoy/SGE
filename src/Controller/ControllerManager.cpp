#include "ControllerManager.h"


void sge::ControllerManager::processEvent(sf::Event event){
    for(std::function<void(sf::Event)> controller : m_components){
        controller(event);
    }
}