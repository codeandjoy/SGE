#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>


namespace sge{
    class Controller{
        public: 
            virtual void script(sf::Event event){};
    };
}


#endif