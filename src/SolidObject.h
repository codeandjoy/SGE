#ifndef SOLID_OBJECT_H
#define SOLID_OBJECT_H

#include "SFML/Graphics.hpp"


class SolidObject{
    public:
        // ? init with *owner's position
        SolidObject(sf::Sprite *owner);

        void updateSolidObject();

        sf::RectangleShape* getCollisionRect();

    private:
        sf::Sprite *ownerPtr;

        sf::RectangleShape collisionRect;
        // bounce
        // friction force
        // etc.
};


#endif