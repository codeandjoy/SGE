#ifndef DRAW_MANAGER_H
#define DRAW_MANAGER_H

#include <SFML/Graphics.hpp>


namespace sge{
    struct DrawManager{
        virtual void draw(sf::RenderWindow* window){};
    };
}


#endif