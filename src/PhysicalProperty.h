#ifndef PHYSICAL_PROPERTY_H
#define PHYSICAL_PROPERTY_H

#include <SFML/Graphics.hpp>


class PhysicalProperty{
    public:
        virtual void updatePhysicalProperty(sf::Transformable *owner) = 0;
};


#endif