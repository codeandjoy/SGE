#ifndef MAP_CONTROLLER_H
#define MAP_CONTROLLER_H

#include "../../SGE.hpp"


class MapController : public sge::Controller{
    public:
        MapController(sge::Entity* boxEntity) : m_boxEntity(boxEntity){}; 

        void script(sf::Event event) override{
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::R){
                    m_boxEntity->sprite->setPosition(sf::Vector2f(360, 160));
                }
            }
        }

    private:
        sge::Entity* m_boxEntity;
};


#endif