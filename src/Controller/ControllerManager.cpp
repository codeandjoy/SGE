#include "ControllerManager.h"
#include "Controller.h"


void sge::ControllerManager::processEvent(sf::Event event){
    for(sge::Controller* controller : m_components){
        controller->script(event);
    }
}