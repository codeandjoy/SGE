#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H


#include <SFML/Graphics.hpp>
#include "PhysicalProperty.h"

class PhysicalObject{
    public:
        PhysicalObject(sf::Transformable *owner);

        void addPhysicalProperty(PhysicalProperty *property);    
        void updatePhysics();

    private:
        sf::Transformable *owner; // TODO vector of owner pointers to allow reuse?
        std::vector<PhysicalProperty*> physicalProperties;
};


#endif