#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <SFML/Graphics.hpp>
#include "PhysicalProperty.h"


class PhysicalObject : public sf::Sprite{
    public:
    void setMovementVector(sf::Vector2f _movementVector); // ? Use movement methods in the future?
    void setMovementVectorX(float x); // ? Use movement methods in the future?
    void setMovementVectorY(float y); // ? Use movement methods in the future?
    sf::Vector2f getMovementVector();

    void setMass(float _mass);
    float getMass();
    
    void setIsFlying(bool is); // ? Use just mass = 0 to 'fly' ?
    bool getIsFlying();

    // void movementAccelerate();
    // void movementSlacken();
    void movementStop();
    void movementStopX();
    void movementStopY();
    // ? void setVelocityCap(...) (sets max possible velocity vector values)
    // ? setMovementFunction(lambda) (sets movement algorithm (e.g. acceleration -> keeping velocity -> slowing down -> stop))
    void update(); // TODO accepts delta time

    private:
    sf::Vector2f movementVector = sf::Vector2f(0, 0);
    float mass = 0;
    bool isFlying = false;
};


#endif