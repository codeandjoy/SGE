#ifndef COLLISION_SHAPE_H
#define COLLISION_SHAPE_H

#include <SFML/Graphics.hpp>
#include "CollisionShapePositionData.h"
#include "../../PhysicsManager/PhysicalObject.h"


class CollisionShape : public sf::RectangleShape{
    public:
        CollisionShape(PhysicalObject *_owner);

        PhysicalObject* getOwner();

        CollisionShapePositionData getPositionData();

        bool getIsVisible();
        void setIsVisible(bool is);

        sf::Vector2f getOffset();
        void setOffset(sf::Vector2f _offset);

        void align();

    private:
        PhysicalObject *owner;

        bool isVisible = true;
        sf::Vector2f offset = sf::Vector2f(0, 0);
};


#endif