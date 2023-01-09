#include "Moveable.h"

void Moveable::setIsMovingTop(bool is) { isMovingTop = is; }
void Moveable::setIsMovingBottom(bool is) { isMovingBottom = is; }
void Moveable::setIsMovingRight(bool is) { isMovingRight = is; }
void Moveable::setIsMovingLeft(bool is) { isMovingLeft = is; }

void Moveable::updatePhysicalProperty(sf::Transformable *owner){
    float velocity = .1; // TODO hardcoded velocity

    if(isMovingTop) move(owner, sf::Vector2f(0, -velocity)); 
    else if(isMovingBottom) move(owner, sf::Vector2f(0, velocity)); 
    else if(isMovingRight) move(owner, sf::Vector2f(velocity, 0)); 
    else if(isMovingLeft) move(owner, sf::Vector2f(-velocity, 0)); 
}

void Moveable::move(sf::Transformable *owner, sf::Vector2f movement){
    printf("MOVING\n");
    owner->setPosition(owner->getPosition() + movement);
}