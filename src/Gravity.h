#ifndef GRAVITY_H
#define GRAVITY_H

#include <SFML/Graphics.hpp>
#include "PhysicalProperty.h"


class Gravity : public PhysicalProperty{
    public:
        Gravity(sf::Vector2f value);
    
        void updatePhysicalProperty(sf::Transformable *owner);

    private:
        sf::Vector2f value;
};


#endif