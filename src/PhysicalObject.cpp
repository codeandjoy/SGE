#include "PhysicalObject.h"

void PhysicalObject::setMovementVector(sf::Vector2f _movementVector){ movementVector = _movementVector; }
void PhysicalObject::setMovementVectorX(float x){ movementVector = sf::Vector2f(x, movementVector.y); }
void PhysicalObject::setMovementVectorY(float y){ movementVector = sf::Vector2f(movementVector.x, y); }
sf::Vector2f PhysicalObject::getMovementVector(){ return movementVector; }


void PhysicalObject::setMass(float _mass){ mass = _mass; }
float PhysicalObject::getMass(){ return mass; }

void PhysicalObject::setIsFlying(bool is){ isFlying = is; }
bool PhysicalObject::getIsFlying(){ return isFlying ;}

void PhysicalObject::movementStop(){
    movementVector = sf::Vector2f(0, 0); 
};
void PhysicalObject::movementStopX(){
    movementVector = sf::Vector2f(0, movementVector.y);
};
void PhysicalObject::movementStopY(){
    movementVector = sf::Vector2f(movementVector.x, 0);
};

void PhysicalObject::update(){
    // Movement
    setPosition(getPosition()+movementVector);
};