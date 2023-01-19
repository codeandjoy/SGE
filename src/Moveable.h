#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "SFML/Graphics.hpp"
#include "PhysicalProperty.h"


class Moveable : public PhysicalProperty{
    public:
        void setIsMovingTop(bool is);
        void setIsMovingBottom(bool is);
        void setIsMovingRight(bool is);
        void setIsMovingLeft(bool is);

        void updatePhysicalProperty(sf::Transformable *owner);
        void move(sf::Transformable *owner, sf::Vector2f movement);

    private:
        bool isMovingTop = false;
        bool isMovingBottom = false;
        bool isMovingRight = false;
        bool isMovingLeft = false;
};


#endif