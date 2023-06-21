#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include "../../SGE.hpp"


class KeyboardController : public sge::Controller{
    public:
        KeyboardController(sge::Entity* playerEntity) : m_playerEntityPtr(playerEntity){}; 

        void script(sf::Event event) override{
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::A){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_right");
                    m_playerEntityPtr->stateCluster->activateState("moving_left");
                }
                else if(event.key.code == sf::Keyboard::D){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_left");
                    m_playerEntityPtr->stateCluster->activateState("moving_right");
                }

                if(event.key.code == sf::Keyboard::Space){
                    m_playerEntityPtr->stateCluster->deactivateState("on_ground");
                    m_playerEntityPtr->stateCluster->activateState("jump");
                    if(m_playerEntityPtr->stateCluster->isStateActive("jump")){
                        m_playerEntityPtr->motionUnit->velocity.y = - 200; // ! infinite jump for testing
                    }
                }
            }
            if(event.type == sf::Event::KeyReleased){
                if(event.key.code == sf::Keyboard::A){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_left");
                }
                if(event.key.code == sf::Keyboard::D){
                    m_playerEntityPtr->stateCluster->deactivateState("moving_right");
                }
            }
        }

    private:
        sge::Entity* m_playerEntityPtr;
};


#endif