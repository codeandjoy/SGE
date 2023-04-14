#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>
#include "../utils/Measurements.h"
#include "../Physics/PhysicalObject.h"


class CollisionShape : public sf::RectangleShape{
    public:
        CollisionShape(PhysicalObject *owner);

        sf::Vector2f offset = sf::Vector2f(0, 0);

        PhysicalObject* getOwner();
        Measurements getMeasurements();
        void align();

    private:
        PhysicalObject *m_owner;
};


#endif