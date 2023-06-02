#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <SFML/Graphics.hpp>


namespace sge{
    struct EventManager{
        virtual void processEvent(sf::Event event){};
    };
}



#endif